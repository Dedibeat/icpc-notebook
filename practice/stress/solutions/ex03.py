"""Ex03 solution. Brute: python3 ex03.py < in. Generator: python3 ex03.py SEED.
Bug: a debugging cap `cnt = 100` was left in the cycle walk (1071 G; 2661 J's `l < 3`).
Cycles longer than 101 are cut. Fix: delete the cap.
Generator lesson: tiny tests never reach a cap; mix in larger n (the brute is O(n^2))."""
import random, sys
CE = "102\n" + " ".join(map(str, range(2, 103))) + " 1\n"  # one cycle of length 102
FIX = [("while j != i and cnt:", "while j != i:")]

def gen():
    n = random.choice([random.randint(1, 6), random.randint(100, 300)])
    return f"{n}\n{' '.join(map(str, random.sample(range(1, n + 1), n)))}\n"

def brute(s):
    n, *p = map(int, s.split())
    res = []
    for i in range(1, n + 1):
        j, c = p[i - 1], 1
        while j != i: j, c = p[j - 1], c + 1
        res.append(c)
    return " ".join(map(str, res))

if __name__ == "__main__":
    if len(sys.argv) > 1: random.seed(int(sys.argv[1])); print(gen(), end="")
    else: print(brute(sys.stdin.read()))
