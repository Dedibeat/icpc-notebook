"""stress.py FAST BRUTE [N] -- compare two commands on N random tests from gen()."""
import random, subprocess, sys

def gen():  # EDIT per problem; mix tiny values, edge sizes, several test cases
    n = random.randint(1, 6)
    return f"{n}\n{' '.join(str(random.randint(-3, 3)) for _ in range(n))}\n"

def run(cmd, s):
    return subprocess.run(cmd, shell=True, input=s, capture_output=True,
                          text=True, timeout=5).stdout.split()

for seed in range(int(sys.argv[3]) if len(sys.argv) > 3 else 1000):
    random.seed(seed); s = gen()
    x, y = run(sys.argv[1], s), run(sys.argv[2], s)
    if x != y: sys.exit(f"WA seed {seed}\n{s}fast:  {' '.join(x)}\nbrute: {' '.join(y)}")
print("OK")
