"""Ex01 - Sum of maxima.
Input: n, then a_1..a_n (1 <= n <= 2*10^5, 1 <= a_i <= 10^9).
Output: the sum of max(a_l..a_r) over all 1 <= l <= r <= n.
Sample: "3 / 1 3 2" -> 15"""
n = int(input()); a = list(map(int, input().split()))
L, R, st = [0] * n, [0] * n, []
for i in range(n):
    while st and a[st[-1]] < a[i]: st.pop()
    L[i] = st[-1] if st else -1; st.append(i)
st = []
for i in range(n - 1, -1, -1):
    while st and a[st[-1]] < a[i]: st.pop()
    R[i] = st[-1] if st else n; st.append(i)
print(sum(a[i] * (i - L[i]) * (R[i] - i) for i in range(n)))
