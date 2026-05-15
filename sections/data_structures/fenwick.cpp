// Fenwick tree for prefix sums.
// Complexity: add/sum/rangeSum/lower_bound are O(log n).
// Pitfalls: external indices are 0-based; lower_bound assumes all values nonnegative.
// Usage: Fenwick fw(n); fw.add(i, x); fw.rangeSum(l, r); // [l,r)
struct Fenwick {
    int n;
    vector<long long> bit;
    Fenwick(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }
    void add(int idx, long long val) {
        for (++idx; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    long long sumPrefix(int r) {
        long long res = 0;
        for (; r > 0; r -= r & -r) res += bit[r];
        return res;
    }
    long long rangeSum(int l, int r) {
        return sumPrefix(r) - sumPrefix(l);
    }
    int lower_bound(long long need) {
        // first idx with sumPrefix(idx+1) >= need, or n if total < need
        if (need <= 0) return 0;
        int idx = 0;
        for (int step = 1 << __lg(max(1, n)); step; step >>= 1) {
            int next = idx + step;
            if (next <= n && bit[next] < need) {
                idx = next;
                need -= bit[next];
            }
        }
        return idx;
    }
};
