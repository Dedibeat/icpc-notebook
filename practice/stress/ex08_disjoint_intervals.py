"""Ex08 - Disjoint intervals.
Input: n, then n lines l_i r_i (1 <= n <= 2000, 1 <= l_i <= r_i <= 10^9).
Output: the maximum number of pairwise disjoint intervals (touching ends overlap).
Sample: "3 / 1 2 / 2 3 / 4 5" -> 2"""
n = int(input()); iv = [tuple(map(int, input().split())) for _ in range(n)]
iv.sort(key=lambda x: x[1] - x[0])  # short intervals block the fewest others
taken = []
for l, r in iv:
    if all(r < a or b < l for a, b in taken): taken.append((l, r))
print(len(taken))
