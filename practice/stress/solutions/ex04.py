"""Ex04 solution. Brute: python3 ex04.py < in. Generator: python3 ex04.py SEED.
Bug: when the total is 0, t == 2t, so one prefix is counted as both cuts: the middle part
is empty (2661 B: the p = 0 / q = 0 cases). Fix: add to ans before counting the first cut.
Generator lesson: allow zeros and negatives so the degenerate total 0 appears."""
import random, sys
CE = "2\n0 0\n"  # fast 1, correct 0
FIX = [("    if pre == t: cnt += 1\n    if pre == 2 * t: ans += cnt",
        "    if pre == 2 * t: ans += cnt\n    if pre == t: cnt += 1")]

def gen():
    n = random.randint(1, 6)
    return f"{n}\n{' '.join(str(random.randint(-2, 2)) for _ in range(n))}\n"

def brute(s):
    n, *a = map(int, s.split())
    return str(sum(sum(a[:i]) == sum(a[i:j]) == sum(a[j:])
                   for i in range(1, n) for j in range(i + 1, n)))

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
