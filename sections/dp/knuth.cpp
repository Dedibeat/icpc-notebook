// Knuth optimization for merging intervals. cost(l,r) uses [l,r).
// Require monotone optimal splits: opt(l,r-1) <= opt(l,r) <= opt(l+1,r).
// Example: knuth(n, [&](int l,int r){return pref[r]-pref[l];}) for
// adjacent pile merging with nonnegative weights. Singleton cost is zero.
// O(n^2) time for O(1) cost, n(n+1)/2 stored sums plus O(n) split indices.
// At n=5000 the sums alone take about 100 MB. All costs/sums must fit ll.
template<class Cost>
long long knuth(int n, Cost cost) {
    if (!n) return 0;
    vector<vector<long long>> dp(n); // dp[r][l] represents [l,r+1)
    for (int r = 0; r < n; ++r) dp[r].resize(r+1);
    vector<int> opt(n);
    iota(opt.begin(),opt.end(),0);
    for (int len = 2; len <= n; ++len) {
        for (int l = 0, r = len-1; r < n; ++l, ++r) {
            // Left-to-right: opt[l] and opt[l+1] still describe length len-1.
            long long best = LLONG_MAX;
            int split = opt[l];
            for (int k = opt[l]; k <= min(opt[l+1],r-1); ++k) {
                long long cand = dp[k][l] + dp[r][k+1];
                if (cand < best) best = cand, split = k;
            }
            dp[r][l] = best + cost(l,r+1);
            opt[l] = split;
        }
    }
    return dp[n-1][0];
}
