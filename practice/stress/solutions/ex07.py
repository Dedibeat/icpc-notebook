"""Ex07 solution. Brute: python3 ex07.py < in. Generator: python3 ex07.py SEED.
Bug: pushing -p makes heappop drop the MOST profitable job; it must drop the least
(2661 G: max-heap where a min-heap was needed). Fix: push p, print sum(h).
Generator lesson: small deadlines (1..3) so jobs actually compete for days."""
import random, sys
CE = "2\n1 1\n1 2\n"  # fast 1, correct 2
FIX = [("heappush(h, -p)", "heappush(h, p)"), ("print(-sum(h))", "print(sum(h))")]

def gen():
    n = random.randint(1, 6)
    return f"{n}\n" + "".join(f"{random.randint(1, 3)} {random.randint(1, 10)}\n" for _ in range(n))

def brute(s):
    n, *v = map(int, s.split()); jobs = list(zip(v[::2], v[1::2])); best = 0
    for m in range(1 << n):
        ch = sorted(jobs[i] for i in range(n) if m >> i & 1)
        if all(d > day for day, (d, p) in enumerate(ch)): best = max(best, sum(p for d, p in ch))
    return str(best)

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
