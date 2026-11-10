"""Ex05 solution. Brute: python3 ex05.py < in. Generator: python3 ex05.py SEED.
Bug: the memo survives between test cases, so test 2 reuses test 1's f values
(in C++: a dp array or global filled once). Fix: f.cache_clear() per test.
Generator lesson: always emit several test cases when the input has T."""
import random, sys
CE = "2\n1\n5\n1\n7\n"  # fast 5 5, correct 5 7
FIX = [("    print(f(0))", "    f.cache_clear(); print(f(0))")]

def gen():
    t = random.randint(1, 3); s = f"{t}\n"
    for _ in range(t):
        n = random.randint(1, 5)
        s += f"{n}\n{' '.join(str(random.randint(1, 10)) for _ in range(n))}\n"
    return s

def brute(s):
    it, out = iter(map(int, s.split())), []
    for _ in range(next(it)):
        a = [next(it) for _ in range(next(it))]
        out.append(max(sum(x for i, x in enumerate(a) if m >> i & 1)
                       for m in range(1 << len(a)) if m & m >> 1 == 0))
    return "\n".join(map(str, out))

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
