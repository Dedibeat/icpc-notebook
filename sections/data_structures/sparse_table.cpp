// Sparse table for static idempotent range query, [l, r) with l < r, O(1).
// Build O(n log n). EDIT ONLY op(): must be idempotent (min/max/gcd/and/or).
struct SparseTable {
    static long long op(long long a, long long b) { return min(a, b); }

    vector<vector<long long>> st; // st[j][i] = op over a[i..i+2^j)
    SparseTable() {}
    SparseTable(const vector<long long>& a) { build(a); }
    void build(const vector<long long>& a) {
        st.assign(1, a);
        for (int j = 1; (1 << j) <= (int)a.size(); j++) {
            st.emplace_back(a.size() - (1 << j) + 1);
            for (int i = 0; i < (int)st[j].size(); i++)
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
    long long query(int l, int r) {
        int j = __lg(r - l);
        return op(st[j][l], st[j][r - (1 << j)]);
    }
};
