// Lazy segment tree. 0-indexed, inclusive ranges [l, r]. O(log n) per op.
// To reuse for another operation, edit ONLY the marked block below:
//   types V (node) / L (tag), the two identities, and merge/applyVal/compose.
// Configured for: range-add update, range-sum query.
// Pitfalls: compose(a,f) applies OLD a then NEW f; arithmetic must fit V.
// Input: init(a), then valid 0-indexed inclusive intervals [l,r].
// Effect: update(l,r,x) adds x to each a[i] in [l,r]; l>r does nothing.
// Output: query(l,r) returns the range sum, or VID for l>r.
// See the usage notes for complete, tested alternative configurations.
struct SegTree {
    // ---- customize for the operation -------------------------------------
    using V = long long;          // node value type
    using L = long long;          // lazy tag type
    static constexpr V VID = 0;   // merge identity (returned for empty range)
    static constexpr L LID = 0;   // "no pending update" tag
    static V merge(V a, V b)            { return a + b; }       // combine children
    static V applyVal(V a, L f, int len){ return a + f * len; } // tag over len cells
    static L compose(L a, L f)          { return a + f; }       // apply f on top of a
    // ----------------------------------------------------------------------

    int n;
    vector<V> t;
    vector<L> lz;

    SegTree(int n = 0) { init(n); }
    void init(int n_) { n = max(1, n_); t.assign(4 * n, VID); lz.assign(4 * n, LID); }
    void init(const vector<V>& a) { init((int)a.size()); if (!a.empty()) build(a, 1, 0, n - 1); }

    void apply(int x, L f, int len) {
        t[x] = applyVal(t[x], f, len);
        lz[x] = compose(lz[x], f);
    }
    void push(int x, int l, int r) {
        if (lz[x] == LID) return;
        int m = (l + r) / 2;
        apply(2 * x, lz[x], m - l + 1);
        apply(2 * x + 1, lz[x], r - m);
        lz[x] = LID;
    }
    void build(const vector<V>& a, int x, int l, int r) {
        if (l == r) { t[x] = a[l]; return; }
        int m = (l + r) / 2;
        build(a, 2 * x, l, m);
        build(a, 2 * x + 1, m + 1, r);
        t[x] = merge(t[2 * x], t[2 * x + 1]);
    }
    void update(int x, int l, int r, int ql, int qr, L f) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply(x, f, r - l + 1); return; }
        push(x, l, r);
        int m = (l + r) / 2;
        update(2 * x, l, m, ql, qr, f);
        update(2 * x + 1, m + 1, r, ql, qr, f);
        t[x] = merge(t[2 * x], t[2 * x + 1]);
    }
    V query(int x, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return VID;
        if (ql <= l && r <= qr) return t[x];
        push(x, l, r);
        int m = (l + r) / 2;
        return merge(query(2 * x, l, m, ql, qr), query(2 * x + 1, m + 1, r, ql, qr));
    }
    // Public wrappers: ranges are inclusive.
    void update(int l, int r, L f) { update(1, 0, n - 1, l, r, f); }
    V query(int l, int r)          { return query(1, 0, n - 1, l, r); }
};
