"""Ex11 solution. Brute: python3 ex11.py < in. Generator: python3 ex11.py SEED.
Bug: INF = 10^9 is not larger than every answer (up to ~2*10^14), so a reachable stone
looks unreachable (4593 C, 2575 L: sentinel below real answers). Fix: INF = 10**18.
Generator lesson: some tests need maximal values, not just tiny ones."""
import random, sys
CE = "2\n0 1000000000\n"  # fast -1, correct 1000000000
FIX = [("INF = 10**9", "INF = 10**18")]

def gen():
    n, v = random.randint(2, 6), random.choice([10, 10**9])
    h = [-1 if 0 < i < n - 1 and random.random() < 0.3 else random.randint(0, v) for i in range(n)]
    return f"{n}\n{' '.join(map(str, h))}\n"

def brute(s):
    n, *h = map(int, s.split()); best = -1
    for m in range(1, 1 << n):  # m = set of stones the frog lands on
        p = [i for i in range(n) if m >> i & 1]
        if p[0] == 0 and p[-1] == n - 1 and min(h[i] for i in p) >= 0 \
                and all(y - x <= 2 for x, y in zip(p, p[1:])):
            c = sum(abs(h[y] - h[x]) for x, y in zip(p, p[1:]))
            best = c if best < 0 else min(best, c)
    return str(best)

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
