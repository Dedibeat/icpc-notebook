"""Ex01 solution. Brute: python3 ex01.py < in. Generator: python3 ex01.py SEED.
Bug: both stacks stop at an equal value, so a subarray whose maximum occurs twice is
counted by neither copy (1794 F). Fix: pop on <= on one side.
Generator lesson: values in 1..3 force ties; random values up to 10^9 never repeat."""
import random, sys
CE = "2\n1 1\n"  # fast 2, correct 3
FIX = [("a[st[-1]] < a[i]", "a[st[-1]] <= a[i]")]

def gen():
    n = random.randint(1, 6)
    return f"{n}\n{' '.join(str(random.randint(1, 3)) for _ in range(n))}\n"

def brute(s):
    n, *a = map(int, s.split())
    return str(sum(max(a[l:r + 1]) for l in range(n) for r in range(l, n)))

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
