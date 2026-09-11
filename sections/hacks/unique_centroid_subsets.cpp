// Count nonempty connected vertex subsets with exactly one centroid.
// User-supplied complete solution; formatting only. Input: t, then n and n-1 edges.
// Time O(n^2), memory O(n^2); fixed arrays use about 145 MB even for small n.
// Pitfalls: 1-indexed tree, 1<=n<=3000; recursive DFS may need more stack.
// Modulus is 998244353. g is cleared after each test; DP reset logic is retained.
#include <bits/stdc++.h>
using namespace std;
constexpr long long mod = 998244353;
int t, n, si[3005];
long long dp1[3005][3005], dp2[3005][3005], ans;
vector<int> g[3005];
void dfs1(int v, int fa) {
    for (int i = 0; i <= si[v]; i++) dp1[v][i] = dp2[v][i] = 0;
    si[v] = 1, dp1[v][1] = 1;
    for (int i : g[v]) {
        if (i == fa) continue;
        dfs1(i, v);
        for (int j = si[v]; ~j; j--) for (int k = 1; k <= si[i]; k++)
            dp1[v][j+k] = (dp1[v][j+k] + dp1[v][j]*dp1[i][k]) % mod;
        si[v] += si[i];
    }
    dp1[v][0] = 1;
    for (int i = 1; i <= si[v]; i++) ans += dp1[v][i];
}
void dfs2(int v, int fa) {
    for (int i = 1; i <= si[v]; i++) ans = (ans - dp1[v][i]*dp2[v][i]) % mod;
    for (int i : g[v]) {
        if (i == fa) continue;
        for (int j = 1; j <= si[i]; j++) dp2[i][j] = dp2[v][j-1];
        for (int j : g[v]) {
            if (j == i || j == fa) continue;
            for (int k = si[i]; ~k; k--)
                for (int l = min(si[j], si[i]-k); l; l--)
                    dp2[i][k+l] = (dp2[i][k+l] + dp2[i][k]*dp1[j][l]) % mod;
        }
        dp2[i][0] = 1, dfs2(i, v);
    }
    g[v].clear();
}
int main() {
    cin >> t;
    while (t--) {
        scanf("%d", &n);
        for (int i = 1, x, y; i < n; i++)
            scanf("%d%d", &x, &y), g[x].emplace_back(y), g[y].emplace_back(x);
        ans = 0, dfs1(1, 0), dp2[1][0] = 1, dfs2(1, 0);
        printf("%lld\n", (ans+mod) % mod);
    }
    return 0;
}
