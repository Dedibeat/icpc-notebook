// Sparse table for static idempotent range query, [l, r) with l < r, O(1).
// Build O(n log n). EDIT ONLY op(): must be idempotent (min/max/gcd/and/or).
struct SparseTable {
    static long long op(long long a, long long b) { return min(a, b); }

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
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    long long query(int l, int r) {
        int j = lg[r - l];
        return op(st[j][l], st[j][r - (1 << j)]);
    }
};
