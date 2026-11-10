"""Ex06 solution. Brute: python3 ex06.py < in. Generator: python3 ex06.py SEED.
Bug: `>= 0` tests the upper median; the lower median >= m needs more elements >= m than
< m, i.e. `> 0` (1794 G: median definition). Fix: `> 0`.
Generator lesson: write the brute from the statement's definition, literally."""
import random, sys
CE = "2 2\n1 2\n"  # fast 2, correct 1
FIX = [("pre[i] - mn >= 0", "pre[i] - mn > 0")]

def gen():
    n = random.randint(1, 6); k = random.randint(1, n)
    return f"{n} {k}\n{' '.join(str(random.randint(1, n)) for _ in range(n))}\n"

def brute(s):
    n, k, *a = map(int, s.split())
    return str(max(sorted(a[l:r])[(r - l - 1) // 2]
                   for l in range(n) for r in range(l + k, n + 1)))

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
