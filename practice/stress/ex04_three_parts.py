"""Ex04 - Three equal parts.
Input: n, then a_1..a_n (1 <= n <= 5*10^5, |a_i| <= 10^9).
Output: the number of ways to cut the array into three nonempty contiguous parts
with equal sums.
Sample: "5 / 1 2 3 0 3" -> 2"""
n = int(input()); a = list(map(int, input().split()))
t, pre, cnt, ans = sum(a) // 3, 0, 0, 0
for i in range(n - 1):
    pre += a[i]
    if pre == t: cnt += 1
    if pre == 2 * t: ans += cnt
print(ans if sum(a) % 3 == 0 else 0)
