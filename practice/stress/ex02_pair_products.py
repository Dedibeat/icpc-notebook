"""Ex02 - Pair products.
Input: n, then a_1..a_n (2 <= n <= 2*10^5, 1 <= a_i <= 10^9).
Output: the sum of a_i * a_j over all i < j, modulo 998244353.
Sample: "3 / 1 2 3" -> 11"""
M = 998244353
n = int(input()); a = list(map(int, input().split()))
s = sum(a) % M
q = sum(x * x for x in a) % M
print((s * s - q) // 2 % M)
