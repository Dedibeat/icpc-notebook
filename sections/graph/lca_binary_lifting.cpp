// Binary lifting LCA for rooted trees.
// Complexity: build O(n log n), query O(log n).
// Pitfalls: call build(root); graph must be a tree; recursion depth on large chains.
// Usage: LCA lca(n); add undirected edges to lca.g; lca.build(0); lca.lca(u,v).
struct LCA {
    int n, LOG;
    vector<vector<int>> g, up;
    vector<int> depth;
    LCA(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        LOG = 1;
        while ((1 << LOG) <= max(1, n)) LOG++;
        g.assign(n, {});
        up.assign(LOG, vector<int>(n));
        depth.assign(n, 0);
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs(int v, int p) {
        up[0][v] = p;
        for (int j = 1; j < LOG; j++) up[j][v] = up[j - 1][up[j - 1][v]];
        for (int to : g[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v);
        }
    }
    void build(int root = 0) {
        depth[root] = 0;
        dfs(root, root);
    }
    int lift(int v, int k) {
        for (int j = 0; j < LOG; j++) if (k >> j & 1) v = up[j][v];
        return v;
    }
    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        a = lift(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--) if (up[j][a] != up[j][b]) {
            a = up[j][a];
            b = up[j][b];
        }
        return up[0][a];
    }
    int dist(int a, int b) {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }
};
