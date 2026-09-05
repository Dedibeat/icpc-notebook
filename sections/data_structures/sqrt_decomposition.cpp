// Sqrt decomposition. 0-indexed, half-open ranges [l,r). O(sqrt(n)) per op.
// To reuse for another operation, edit ONLY the marked block below.
// Configured for: range-add update, range-sum query.
// Pitfalls: applyVal must work for both one cell and a whole block;
//           L needs equality with LID. Partial operations push the block tag.
// update(l,r,x) adds x to a[l..r); query(l,r) returns that range's sum.
// Example: SqrtDecomp s({1,2,3}); s.update(1,3,4); s.query(0,3)==14.
struct SqrtDecomp {
    // ---- customize for the operation -------------------------------------
    using V = long long;
    using L = long long;
    static constexpr V VID = 0;
    static constexpr L LID = 0;
    static V merge(V a, V b)             { return a + b; }
    static V applyVal(V a, L f, int len) { return a + f * len; }
    static L compose(L a, L f)           { return a + f; }
    // ----------------------------------------------------------------------

    int n, B, blocks;
    vector<V> a, aggregate;
    vector<L> lazy;

    SqrtDecomp(const vector<V>& values) : n(values.size()), a(values) {
        B = max(1, (int)sqrt(max(1, n)) + 1);
        blocks = (n + B - 1) / B;
        aggregate.assign(blocks, VID);
        lazy.assign(blocks, LID);
        for (int i = 0; i < n; ++i)
            aggregate[i / B] = merge(aggregate[i / B], a[i]);
    }
    int block_end(int b) const { return min(n, (b + 1) * B); }

    void rebuild(int b) {
        aggregate[b] = VID;
        for (int i = b * B; i < block_end(b); ++i)
            aggregate[b] = merge(aggregate[b], a[i]);
    }
    void push(int b) {
        if (lazy[b] == LID) return;
        for (int i = b * B; i < block_end(b); ++i)
            a[i] = applyVal(a[i], lazy[b], 1);
        lazy[b] = LID;
    }
    void update(int l, int r, L f) {
        while (l < r) {
            int b = l / B, e = block_end(b);
            if (l == b * B && e <= r) {
                aggregate[b] = applyVal(aggregate[b], f, e - l);
                lazy[b] = compose(lazy[b], f);
                l = e;
            } else {
                push(b);
                int stop = min(r, e);
                while (l < stop) a[l] = applyVal(a[l], f, 1), ++l;
                rebuild(b);
            }
        }
    }
    V query(int l, int r) {
        V ans = VID;
        while (l < r) {
            int b = l / B, e = block_end(b);
            if (l == b * B && e <= r) {
                ans = merge(ans, aggregate[b]);
                l = e;
            } else {
                push(b);
                int stop = min(r, e);
                while (l < stop) ans = merge(ans, a[l++]);
            }
        }
        return ans;
    }
};
