// Sparse table for static range minimum query.
// Complexity: build O(n log n), query O(1).
// Pitfalls: query range is [l,r); idempotent operations only unless adapted.
// Usage: SparseTable st(a); st.query(l, r);
struct SparseTable {
    vector<vector<long long>> st;
    vector<int> lg;
    SparseTable() {}
    SparseTable(const vector<long long>& a) { build(a); }
    void build(const vector<long long>& a) {
        int n = (int)a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        st.assign(lg[n] + 1, vector<long long>(n));
        st[0] = a;
        for (int j = 1; j < (int)st.size(); j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    long long query(int l, int r) {
        int j = lg[r - l];
        return min(st[j][l], st[j][r - (1 << j)]);
    }
};
