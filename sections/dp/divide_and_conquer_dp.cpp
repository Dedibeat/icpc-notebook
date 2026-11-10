// Minimize cost of exactly groups nonempty intervals partitioning [0,n).
// cost(k,j) is the cost of [k,j). Smallest optimal k must be monotone in j.
// Example: squared segment sum with nonnegative elements, using prefix sums.
// O(groups * n log n) time for O(1) cost, O(n) space. Sums must fit long long.
template<class Cost>
long long divide_and_conquer_dp(int n, int groups, Cost cost) {
    if (!n && !groups) return 0;
    assert(1 <= groups && groups <= n);
    vector<long long> prev(n+1), cur(n+1);
    for (int j = 1; j <= n; ++j) prev[j] = cost(0,j);
    auto comp = [&](auto&& self, int l, int r, int lo, int hi) -> void {
        if (l > r) return;
        int mid = (l+r)/2, opt = lo;
        long long best = LLONG_MAX;
        for (int k = lo; k <= min(hi,mid-1); ++k) {
            long long cand = prev[k] + cost(k,mid);
            if (cand < best) best = cand, opt = k;
        }
        cur[mid] = best;
        self(self,l,mid-1,lo,opt);
        self(self,mid+1,r,opt,hi);
    };
    for (int g = 2; g <= groups; ++g) {
        comp(comp,g,n,g-1,n-1);
        prev.swap(cur);
    }
    return prev[n];
}
