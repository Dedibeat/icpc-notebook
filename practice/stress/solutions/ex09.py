"""Ex09 solution. Brute: python3 ex09.py < in. Generator: python3 ex09.py SEED.
Bug: the degree sum is necessary, not sufficient: with n >= 2 every degree must be >= 1
(2661 B: the missing global check). Fix: also require min(d) > 0 when n > 1.
Generator lesson: let values hit 0; brute over all trees via Pruefer sequences."""
import random, sys
from itertools import product
CE = "2\n0 2\n"  # fast YES, correct NO
FIX = [("sum(d) == 2 * (n - 1)", "sum(d) == 2 * (n - 1) and (n == 1 or min(d) > 0)")]

def gen():
    n = random.randint(1, 5)
    return f"{n}\n{' '.join(str(random.randint(0, 3)) for _ in range(n))}\n"

def brute(s):
    n, *d = map(int, s.split())
    ok = d == [0] if n == 1 else any([q.count(v) + 1 for v in range(n)] == d
                                     for q in product(range(n), repeat=n - 2))
    return "YES" if ok else "NO"

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
