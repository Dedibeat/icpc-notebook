"""Ex07 - Jobs with deadlines.
Input: n, then n lines d_i p_i (1 <= n <= 2*10^5, 1 <= d_i <= n, 1 <= p_i <= 10^9).
Each job takes one day and earns p_i if done on a day <= d_i; one job per day.
Output: the maximum total profit.
Sample: "3 / 1 2 / 1 2 / 2 2" -> 4"""
import heapq
n = int(input()); jobs = sorted(tuple(map(int, input().split())) for _ in range(n))
h = []
for d, p in jobs:
    heapq.heappush(h, -p)
    if len(h) > d: heapq.heappop(h)
print(-sum(h))
