// Divide & conquer DP optimization: dp_cur[j] = min_k(dp_bef[k-1] + cost(k,j)).
// Valid when opt(j) is non-decreasing in j (e.g. cost satisfies quadrangle
// inequality). O(m n log n) instead of O(m n^2). 1-indexed.
// Example: split a[1..n] into m groups, cost of a group = (sum)^2.
// WARNING: (sum)^2 cost needs a[i] >= 0 (monotone prefix sums), else QI fails.
// Input: n m, then n nonnegative values; requires 1<=m<=n.
// Output: minimum sum of squared group sums over exactly m nonempty intervals.
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 5;
int n, m;
vector<int> dp_bef, dp_cur;
int a[N], pref[N];
// EDIT ONLY cost(): comp() below is the optimization machinery.
int cost(int l, int r) {
    int sum = pref[r] - pref[l - 1];
    return sum * sum;
}
void comp(int l, int r, int lo, int hi) { // fill dp_cur[l..r]; opt is in [lo,hi]
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<int, int> best = {(int)1e18, -1};
    for (int k = lo; k <= min(hi, mid); k++)
        best = min(best, make_pair((k ? dp_bef[k - 1] : 0) + cost(k, mid), k));
    dp_cur[mid] = best.first;
    int opt = best.second;
    comp(l, mid - 1, lo, opt);
    comp(mid + 1, r, opt, hi);
}
int32_t main() {
    ios::sync_with_stdio(0); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    dp_cur.assign(n + 1, 0);
    for (int j = 1; j <= n; j++) dp_cur[j] = cost(1, j);
    dp_bef = dp_cur;
    for (int i = 2; i <= m; i++) {
        comp(1, n, 1, n);
        dp_bef = dp_cur;
    }
    cout << dp_cur[n] << '\n';
}
