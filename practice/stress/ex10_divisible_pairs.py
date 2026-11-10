"""Ex10 - Divisible pair sums.
Input: n k, then a_1..a_n (1 <= n, k <= 2*10^5, 1 <= a_i <= 10^9).
Output: the number of pairs i < j with a_i + a_j divisible by k.
Sample: "4 3 / 1 2 3 6" -> 2"""
n, k = map(int, input().split()); c = [0] * k
for x in map(int, input().split()): c[x % k] += 1
ans = c[0] * (c[0] - 1) // 2
for r in range(1, (k + 1) // 2):
    ans += c[r] * c[k - r]
print(ans)
