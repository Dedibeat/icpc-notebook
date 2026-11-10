"""Ex11 - Frog on stones.
Input: n, then h_1..h_n (2 <= n <= 2*10^5; 0 <= h_i <= 10^9, or h_i = -1 for a broken
stone; stones 1 and n are never broken). The frog jumps from stone i to i+1 or i+2,
never onto a broken stone, and pays |h_i - h_j| per jump.
Output: the minimum total cost from stone 1 to stone n, or -1 if impossible.
Sample: "4 / 10 -1 30 10" -> 40"""
n = int(input()); h = list(map(int, input().split()))
INF = 10**9
d = [INF] * n; d[0] = 0
for i in range(1, n):
    for j in (i - 1, i - 2):
        if j >= 0 and h[i] >= 0 and h[j] >= 0:
            d[i] = min(d[i], d[j] + abs(h[i] - h[j]))
print(d[-1] if d[-1] < INF else -1)
