// Knuth optimization: dp[i][j] = min_{i<=k<j}(dp[i][k]+dp[k+1][j]) + C(i,j).
// Valid when opt[i][j-1] <= opt[i][j] <= opt[i+1][j], e.g. C satisfies the
// quadrangle inequality and is monotone on inclusion. O(n^2) total.
// 1-indexed. Example: merge-stones cost C(i,j) = sum a[i..j].
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e3 + 5;
int a[N], pref[N];
int dp[N][N], opt[N][N];
// EDIT ONLY C(): the interval cost. The loops below are the optimization.
int C(int l, int r) { return pref[r] - pref[l - 1]; }
int32_t main() {
    ios::sync_with_stdio(0); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++) opt[i][i] = i;
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            pair<int, int> best = {(int)1e18, -1};
            for (int k = max(i, opt[i][j - 1]); k <= min(opt[i + 1][j], j - 1); k++)
                best = min(best, make_pair(dp[i][k] + dp[k + 1][j], k));
            dp[i][j] = best.first + C(i, j);
            opt[i][j] = best.second;
        }
    }
    cout << dp[1][n] << "\n";
}
