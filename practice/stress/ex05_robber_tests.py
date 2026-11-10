"""Ex05 - Robber, many tests.
Input: T, then T tests: n, then a_1..a_n (1 <= a_i <= 10^9; sum of n <= 500).
Output: per test, the maximum sum of chosen elements with no two adjacent.
Sample: "1 / 4 / 1 2 3 1" -> 4"""
from functools import cache

@cache
def f(i):  # best sum from a[i:]
    return 0 if i >= n else max(f(i + 1), a[i] + f(i + 2))

for _ in range(int(input())):
    n = int(input()); a = list(map(int, input().split()))
    print(f(0))
