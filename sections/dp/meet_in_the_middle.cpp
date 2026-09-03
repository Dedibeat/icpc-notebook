// Maximum subset sum <= limit by meet in the middle.
// Complexity: O(2^(n/2) log 2^(n/2)); practical for n about 40-44.
// Pitfalls: returns LLONG_MIN if no subset fits (possible when limit < 0).
// Usage: long long best=max_subset_sum_leq(a,limit).
vector<long long> half_sums(const vector<long long>& a, int l, int r) {
    vector<long long> sums(1, 0);
    for (int i = l; i < r; ++i) {
        int old = sums.size();
        sums.resize(2 * old);
        for (int j = 0; j < old; ++j) sums[old + j] = sums[j] + a[i];
    }
    return sums;
}

long long max_subset_sum_leq(const vector<long long>& a, long long limit) {
    int m = a.size() / 2;
    auto left = half_sums(a, 0, m), right = half_sums(a, m, a.size());
    sort(right.begin(), right.end());
    long long ans = LLONG_MIN;
    for (long long x : left) {
        auto it = upper_bound(right.begin(), right.end(), limit - x);
        if (it != right.begin()) ans = max(ans, x + *prev(it));
    }
    return ans;
}
