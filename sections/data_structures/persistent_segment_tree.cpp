// Persistent segment tree: k-th smallest value in a[l..r) in O(log M).
// Input: ranks in [0,M); root 0 is empty and prefix roots preserve old versions.
// root[i] stores frequencies in prefix a[0..i). upd(old,pos) adds one value
// without changing old. kth(root[l],root[r],k) selects the 1-based k-th rank
// in a[l..r). Output: kth returns a rank; cnt(root,lo,hi) counts [lo,hi).
// Coordinate-compress/decompress outside the tree. Memory O(n log M).
struct PST {
    struct N { int l, r, cnt; };
    vector<N> t{{0, 0, 0}}; // node 0 = empty tree, usable as initial root
    int M;
    PST(int M) : M(M) { t.reserve(1 << 20); }
    int upd(int u, int pos) { return upd(u, 0, M, pos); }
    int upd(int u, int lo, int hi, int pos) {
        t.push_back(t[u]);
        int v = (int)t.size() - 1;
        t[v].cnt++;
        if (hi - lo == 1) return v;
        int mid = (lo + hi) / 2;
        if (pos < mid) { int c = upd(t[v].l, lo, mid, pos); t[v].l = c; }
        else { int c = upd(t[v].r, mid, hi, pos); t[v].r = c; }
        return v;
    }
    int kth(int a, int b, int k) { return kth(a, b, 0, M, k); }
    int kth(int a, int b, int lo, int hi, int k) {
        if (hi - lo == 1) return lo;
        int mid = (lo + hi) / 2, cl = t[t[b].l].cnt - t[t[a].l].cnt;
        if (k <= cl) return kth(t[a].l, t[b].l, lo, mid, k);
        return kth(t[a].r, t[b].r, mid, hi, k - cl);
    }
    int cnt(int u, int lo, int hi) { return cnt(u, 0, M, lo, hi); }
    int cnt(int u, int l, int r, int lo, int hi) {
        if (!u || hi <= l || r <= lo) return 0;
        if (lo <= l && r <= hi) return t[u].cnt;
        int mid = (l + r) / 2;
        return cnt(t[u].l, l, mid, lo, hi) + cnt(t[u].r, mid, r, lo, hi);
    }
};
