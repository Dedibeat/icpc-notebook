"""Ex06 - Maximum median.
Input: n k, then a_1..a_n (1 <= k <= n <= 2*10^5, 1 <= a_i <= n).
Output: the largest median over all subarrays of length >= k. The median of m numbers
is the ceil(m/2)-th smallest (the lower middle one when m is even).
Sample: "3 3 / 1 3 2" -> 2"""
n, k = map(int, input().split()); a = list(map(int, input().split()))

def ok(m):  # does some subarray of length >= k have median >= m?
    pre, mn = [0], n
    for x in a: pre.append(pre[-1] + (1 if x >= m else -1))
    for i in range(k, n + 1):
        mn = min(mn, pre[i - k])
        if pre[i] - mn >= 0: return True
    return False

lo, hi = 1, n
while lo < hi:
    mid = (lo + hi + 1) // 2
    if ok(mid): lo = mid
    else: hi = mid - 1
print(lo)
