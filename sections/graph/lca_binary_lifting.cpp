// Binary lifting LCA for rooted trees. Also provides dfs-order tin
// (used by virtual_tree.cpp) and kth-ancestor lift.
// Complexity: build O(n log n), query O(log n).
// addEdge loads the tree; build(root) fixes parents/depths. lift(v,k) moves k
// parent edges (stays at root above it); lca/dist query two built vertices.
// Example on edges 0-1,1-2,1-3 rooted at 0: lca(2,3)==1; dist(2,3)==2.
// Pitfalls: build before queries; graph must be a tree; recursion depth on chains.
struct LCA {
    int n, LOG, timer = 0;
    vector<vector<int>> g, up;
    vector<int> depth, tin;
    LCA(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        LOG = 1;
        while ((1 << LOG) <= max(1, n)) LOG++;
        g.assign(n, {});
        up.assign(LOG, vector<int>(n));
        depth.assign(n, 0);
        tin.assign(n, 0);
        timer = 0;
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs(int v, int p) {
        tin[v] = timer++;
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
