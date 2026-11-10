"""Stress kit (tools/stress.sh, tools/stress.py, tools/gen.py, sections/misc/stress.*)
and practice/stress exercises: the tools catch WA/RE/TLE, every planted bug passes its
sample, fails its counterexample and is found by the reference generator, and every
documented fix agrees with the brute force.  Run: python tests/test_stress.py"""
import contextlib, importlib.util, io, random, re, shutil, subprocess, sys, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EX = ROOT / "practice" / "stress"
PY = Path(sys.executable).as_posix()


def run_src(src, s):
    """Run a stdin/stdout program in-process; a crash counts as an output."""
    out, old = io.StringIO(), sys.stdin
    sys.stdin = io.StringIO(s)
    try:
        with contextlib.redirect_stdout(out):
            exec(compile(src, "exercise", "exec"), {"__name__": "__main__"})
    except Exception as e:
        return ["crash:" + type(e).__name__]
    finally:
        sys.stdin = old
    return out.getvalue().split()


def load(path):
    spec = importlib.util.spec_from_file_location(path.stem, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def check_exercise(path, seeds=2000, fix_seeds=200):
    sol = load(EX / "solutions" / (path.name[:4] + ".py"))
    src = path.read_text(encoding="utf-8")
    inp, exp = re.search(r'Sample: "(.*)" -> ([^"\n]*)', src).groups()
    inp = inp.replace(" / ", "\n") + "\n"
    assert run_src(src, inp) == exp.split() == sol.brute(inp).split(), "sample"
    assert run_src(src, sol.CE) != sol.brute(sol.CE).split(), "counterexample passes"
    fixed = src
    for old, new in sol.FIX:
        assert old in fixed, f"FIX target missing: {old!r}"
        fixed = fixed.replace(old, new, 1)
    assert run_src(fixed, sol.CE) == sol.brute(sol.CE).split(), "fix fails counterexample"
    found = None
    for seed in range(seeds):
        random.seed(seed)
        s = sol.gen()
        want = sol.brute(s).split()
        if seed < fix_seeds:
            assert run_src(fixed, s) == want, f"fix fails on seed {seed}:\n{s}"
        if found is None and run_src(src, s) != want:
            found = seed
        if found is not None and seed >= fix_seeds:
            break
    assert found is not None, f"generator never finds the bug in {seeds} seeds"
    return found


def test_exercises():
    files = sorted(EX.glob("ex[0-9][0-9]_*.py"))
    assert len(files) == 11
    for path in files:
        print(f"{path.name}: bug found at seed {check_exercise(path)}, fix OK")


def write(tmp, name, code):
    (tmp / name).write_text(code, encoding="utf-8")
    return f"{PY} {(tmp / name).as_posix()}"


def programs(tmp):
    read = "input(); a = list(map(int, input().split()))\n"
    return dict(
        good=write(tmp, "good.py", read + "print(sum(a))\n"),
        bad=write(tmp, "bad.py", read + "print(sum(x for x in a if x > 0))\n"),
        tle=write(tmp, "tle.py", read + "while a[0] == 0: pass\nprint(sum(a))\n"),
        brute=write(tmp, "brute.py", read + "s = 0\nfor x in a: s += x\nprint(s)\n"),
    )


def test_stress_py():
    with tempfile.TemporaryDirectory() as t:
        p = programs(Path(t))
        for path in ("tools/stress.py", "sections/misc/stress.py"):
            tool = [sys.executable, str(ROOT / path)]
            r = subprocess.run(tool + [p["good"], p["brute"], "30"], capture_output=True, text=True)
            assert r.returncode == 0 and r.stdout.strip() == "OK", r
            r = subprocess.run(tool + [p["bad"], p["brute"], "30"], capture_output=True, text=True)
            assert r.returncode == 1 and r.stderr.startswith("WA seed"), r
            print(f"{path}: OK on a correct program, WA on a wrong one")


def bash():
    sh = shutil.which("bash")
    return None if sh and "system32" in sh.lower() else sh  # WSL's bash cannot see C:/ paths


def test_stress_sh():
    sh = bash()
    if not sh:
        print("stress.sh: SKIPPED (no bash)")
        return
    with tempfile.TemporaryDirectory() as t:
        p, gen = programs(Path(t)), f"{PY} {(ROOT / 'tools' / 'gen.py').as_posix()}"
        def run(fast, n):
            return subprocess.run([sh, (ROOT / "tools" / "stress.sh").as_posix(), fast, p["brute"], gen, n],
                                  cwd=t, capture_output=True, text=True)
        r = run(p["good"], "20")
        assert r.returncode == 0 and r.stdout.strip() == "OK 20 tests", r
        r = run(p["bad"], "50")
        assert r.returncode == 1 and r.stdout.startswith("WA seed"), r
        r = run(p["tle"], "50")
        assert r.returncode == 1 and r.stdout.startswith("RE/TLE seed"), r
        seed = r.stdout.split()[2]
        again = subprocess.run([sys.executable, str(ROOT / "tools" / "gen.py"), seed], capture_output=True, text=True)
        assert r.stdout.split("\n", 1)[1] == again.stdout, "gen.py is not reproducible"
        print("stress.sh: OK, WA and RE/TLE detected; failing seed reproduces")


def test_stress_cpp():
    src = (ROOT / "sections" / "misc" / "stress.cpp").read_text(encoding="utf-8")
    bug = src.replace("cur = max(cur + x, x)", "cur = max(cur + x, 0LL)")
    assert bug != src
    with tempfile.TemporaryDirectory() as t:
        for name, code, ok in (("ok", src, True), ("bug", bug, False)):
            cpp, exe = Path(t) / f"{name}.cpp", Path(t) / name
            cpp.write_text(code, encoding="utf-8")
            subprocess.run(["g++", "-std=c++17", "-O2", "-Wall", "-Wextra", "-Werror", str(cpp), "-o", str(exe)], check=True)
            r = subprocess.run([str(exe)], capture_output=True, text=True)
            assert (r.returncode == 0 and r.stdout == "OK\n") if ok else (r.returncode == 1 and "fast 0" in r.stdout), r
    print("stress.cpp: OK when correct, prints the failing test when wrong")


if __name__ == "__main__":
    test_stress_cpp()
    test_stress_py()
    test_stress_sh()
    test_exercises()
    print("all stress tests passed")
