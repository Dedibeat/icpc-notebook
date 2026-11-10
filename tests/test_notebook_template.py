"""Syntax-check each copyable snippet with the actual contest preamble."""
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import re
import subprocess
import sys


ROOT = Path(__file__).resolve().parents[1]
FILES = {p.stem: p for p in (ROOT / "sections").rglob("*.cpp")}
PREAMBLE = (ROOT / "template.cpp").read_text(encoding="utf-8").split("void solve()")[0]
DEPS = {
    "block_cut_tree_example": ["dsu", "lca_binary_lifting", "block_cut_tree"],
    "virtual_tree": ["lca_binary_lifting"],
    "kruskal_mst": ["dsu"],
    "min_cut_modeling": ["dinic_2"],
    "max_clique": ["dinic_2"],  # vi and sz
    "fft_mod": ["fft_v2"],
    "formal_power_series": ["ntt"],
    "CRT": ["NT_essentials"],
    "primitive_root": ["NT_essentials"],
    "discrete_mod": ["NT_essentials", "primitive_root", "custom_hash"],
    "discrete_log": ["custom_hash"],
    "random_hashing": ["rand_mt19937_faster"],
    "minkowski_sum": ["integer_geometry"],
}
for name in ("convex_hull", "circle_tangents", "minimum_enclosing_circle",
             "half_plane_intersection", "closest_pair", "convex_point_query"):
    DEPS[name] = ["geometry_base"]


def check(name):
    source = FILES[name].read_text(encoding="utf-8")
    if not re.search(r"^\s*(?:signed|int|int32_t)\s+main\s*\(", source, re.M):
        includes = "".join(f'#include "{FILES[d].as_posix()}"\n' for d in DEPS.get(name, []))
        if name == "quick_select":
            source = "void demo(){ vector<int> a{1}; int k=0;\n" + source + "\n}"
        else:
            source = f'#include "{FILES[name].as_posix()}"\n'
        source = PREAMBLE + includes + source + "\nsigned main(){}\n"
    result = subprocess.run(
        ["g++", "-std=c++17", "-fsyntax-only", "-x", "c++", "-"],
        input=source, encoding="utf-8", capture_output=True, cwd=ROOT,
    )
    return name, result.stderr if result.returncode else ""


if __name__ == "__main__":
    skip = {"gnu_extensions", "simulated_annealing"}  # intentionally partial examples
    if sys.platform != "linux":
        skip.add("deep_recursion_stack")
    names = sorted(set(FILES) - skip)
    with ThreadPoolExecutor(max_workers=6) as pool:
        failures = [(name, msg) for name, msg in pool.map(check, names) if msg]
    for name, msg in failures:
        print(f"{name}:\n{msg}")
    print(f"Compiled {len(names) - len(failures)}/{len(names)} snippets")
    print("Skipped:", ", ".join(sorted(skip)))
    sys.exit(bool(failures))
