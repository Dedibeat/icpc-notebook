"""Ex03 - Cycle lengths.
Input: n, then a permutation p_1..p_n of 1..n (1 <= n <= 2*10^5).
Output: for each i, the length of the cycle of p that contains i.
Sample: "4 / 2 1 4 3" -> 2 2 2 2"""
n = int(input()); p = [int(x) - 1 for x in input().split()]
ans = [0] * n
for i in range(n):
    if ans[i]: continue
    cyc, j, cnt = [i], p[i], 100
    while j != i and cnt:
        cyc.append(j); j = p[j]; cnt -= 1
    for v in cyc: ans[v] = len(cyc)
print(*ans)
