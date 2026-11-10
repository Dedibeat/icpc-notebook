// Iterative segment tree: point set and ordered range query [l,r).
// Build O(n), set/query O(log n), memory O(n).
// Edit V, op and ID; op must be associative, ID its identity.
// Pitfalls: 0 <= l <= r <= n; set needs p < n; arithmetic must fit V.
// For noncommutative ops, use query(0,n), not t[1], for the full result.
// Example: ShortST s; s.build({1,2,3}); s.set(1,5); // query(0,3)==9
struct ShortST {
    using V = long long;
    static constexpr V ID = 0;
    static V op(V a, V b) { return a + b; }
    int n;
    vector<V> t;
    ShortST(int n = 0) : n(n), t(2*n, ID) {}
    void build(const vector<V>& a) {
        n = a.size();
        t.assign(2*n, ID);
        copy(a.begin(), a.end(), t.begin() + n);
        for (int i = n-1; i > 0; --i) t[i] = op(t[2*i], t[2*i+1]);
    }
    void set(int p, V x) {
        for (t[p += n] = x; p >>= 1; ) t[p] = op(t[2*p], t[2*p+1]);
    }
    V query(int l, int r) {
        V left = ID, right = ID;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) left = op(left, t[l++]);
            if (r&1) right = op(t[--r], right);
        }
        return op(left, right);
    }
};
