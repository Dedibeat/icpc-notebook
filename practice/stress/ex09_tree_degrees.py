"""Ex09 - Tree degrees.
Input: n, then d_1..d_n (1 <= n <= 2*10^5, 0 <= d_i <= n).
Output: YES if some tree on vertices 1..n gives vertex i exactly d_i edges, else NO.
Sample: "4 / 1 3 1 1" -> YES"""
n = int(input()); d = list(map(int, input().split()))
print("YES" if sum(d) == 2 * (n - 1) else "NO")
