"""Ex10 solution. Brute: python3 ex10.py < in. Generator: python3 ex10.py SEED.
Bug: for even k the residue k/2 pairs with itself and is never counted
(2693 F, 1096 C: a missing or symmetric case). Fix: add C(c[k/2], 2) when k is even.
Generator lesson: small k of both parities; small values so residues repeat."""
import random, sys
CE = "2 2\n1 1\n"  # fast 0, correct 1
FIX = [("print(ans)", "if k % 2 == 0: ans += c[k // 2] * (c[k // 2] - 1) // 2\nprint(ans)")]

def gen():
    n, k = random.randint(1, 6), random.randint(1, 6)
    return f"{n} {k}\n{' '.join(str(random.randint(1, 10)) for _ in range(n))}\n"

def brute(s):
    n, k, *a = map(int, s.split())
    return str(sum((a[i] + a[j]) % k == 0 for i in range(n) for j in range(i + 1, n)))

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
