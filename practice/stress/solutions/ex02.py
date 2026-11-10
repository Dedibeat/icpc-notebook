"""Ex02 solution. Brute: python3 ex02.py < in. Generator: python3 ex02.py SEED.
Bug: `// 2` after `% M`. Halving is exact only while nothing was reduced; after the
reduction s*s - q can be odd (4607 C, 1071 A: modular slips). Fix: multiply by the
inverse of 2.
Generator lesson: some tests need values up to 10^9, or the modulus is never reached."""
import random, sys
CE = "2\n1 1000000000\n"
FIX = [("(s * s - q) // 2 % M", "(s * s - q) * pow(2, M - 2, M) % M")]

def gen():
    n, v = random.randint(2, 4), random.choice([10, 10**9])
    return f"{n}\n{' '.join(str(random.randint(1, v)) for _ in range(n))}\n"

def brute(s):
    n, *a = map(int, s.split())
    return str(sum(a[i] * a[j] for i in range(n) for j in range(i + 1, n)) % 998244353)

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
