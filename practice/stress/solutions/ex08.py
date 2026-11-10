"""Ex08 solution. Brute: python3 ex08.py < in. Generator: python3 ex08.py SEED.
Bug: "shortest first" is an unproven greedy; [4,7] blocks both [1,5] and [6,10]
(4071 A, 1053 A, 2524 C, 4607 D: unproven ideas). Fix: sort by right end.
Generator lesson: the brute (all subsets) refutes a greedy in seconds; do it before run 1."""
import random, sys
from itertools import combinations
CE = "3\n1 5\n6 10\n4 7\n"  # fast 1, correct 2
FIX = [("key=lambda x: x[1] - x[0]", "key=lambda x: x[1]")]

def gen():
    n, s = random.randint(1, 5), ""
    for _ in range(n):
        l = random.randint(1, 10); s += f"{l} {random.randint(l, 10)}\n"
    return f"{n}\n{s}"

def brute(s):
    n, *v = map(int, s.split()); iv = list(zip(v[::2], v[1::2]))
    return str(max(len(c) for k in range(n + 1) for c in combinations(iv, k)
                   if all(b < x or y < a for (a, b), (x, y) in combinations(c, 2))))

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
