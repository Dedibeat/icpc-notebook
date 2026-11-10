import random, sys
random.seed(int(sys.argv[1]))  # seed from stress.sh: same seed, same test
R = random.randint
n = R(1, 6)  # tiny n: the failing test stays readable
print(n)
print(*[R(-3, 3) for _ in range(n)])  # tiny values: ties, zeros, negatives
