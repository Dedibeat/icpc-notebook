// HLD: path/subtree update+query in O(log^2 n) on top of SegTree from
// lazy_segment_tree.cpp (print that first; configure its marked block for
// the needed op — default range add / range sum works as-is).
// 0-indexed, rooted at 0. VALS_EDGES=false: values on vertices, path includes
// both endpoints. VALS_EDGES=true: values on edges, stored at the DEEPER
// endpoint; the LCA vertex is skipped automatically.
// Usage: HLD<false> h(adj); h.modifyPath(u,v,x); h.queryPath(u,v);
//        h.modifySubtree(v,x); h.querySubtree(v); pos[v] = index in tree.
// Pitfalls: recursive dfs on ~2e5 chain; for a non-commutative SegTree::merge
// queryPath combines chain segments in arbitrary order (sum/min/max are fine).
template <bool VALS_EDGES> struct HLD {
    int N, tim = 0;
    vector<vector<int>> adj;
    vector<int> par, siz, rt, pos;
    SegTree tree;
    HLD(vector<vector<int>> adj_)
        : N(adj_.size()), adj(adj_), par(N, -1), siz(N, 1),
          rt(N), pos(N), tree(N) {
        dfsSz(0); dfsHld(0);
    }
    void dfsSz(int v) {
        if (par[v] != -1) adj[v].erase(find(adj[v].begin(), adj[v].end(), par[v]));
        for (int& u : adj[v]) {
            par[u] = v;
            dfsSz(u);
            siz[v] += siz[u];
            if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
        }
    }
    void dfsHld(int v) {
        pos[v] = tim++;
        for (int u : adj[v]) {
            rt[u] = (u == adj[v][0] ? rt[v] : u);
            dfsHld(u);
        }
    }
    template <class B> void process(int u, int v, B op) { // op gets [l, r), may be empty
        for (; rt[u] != rt[v]; v = par[rt[v]]) {
            if (pos[rt[u]] > pos[rt[v]]) swap(u, v);
            op(pos[rt[v]], pos[v] + 1);
        }
        if (pos[u] > pos[v]) swap(u, v);
        op(pos[u] + VALS_EDGES, pos[v] + 1);
    }
    void modifyPath(int u, int v, SegTree::L x) {
        process(u, v, [&](int l, int r) { if (l < r) tree.update(l, r - 1, x); });
    }
    SegTree::V queryPath(int u, int v) {
        SegTree::V res = SegTree::VID;
        process(u, v, [&](int l, int r) {
            if (l < r) res = SegTree::merge(res, tree.query(l, r - 1));
        });
        return res;
    }
    void modifySubtree(int v, SegTree::L x) {
        int l = pos[v] + VALS_EDGES, r = pos[v] + siz[v];
        if (l < r) tree.update(l, r - 1, x);
    }
    SegTree::V querySubtree(int v) {
        int l = pos[v] + VALS_EDGES, r = pos[v] + siz[v];
        return l < r ? tree.query(l, r - 1) : SegTree::VID;
    }
};
