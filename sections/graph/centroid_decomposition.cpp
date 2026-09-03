// Centroid decomposition of a tree/forest. Parent[] is the centroid tree.
// Complexity: O(n log n) time, O(n) memory.
// Pitfalls: recursive DFS can overflow on a long chain; build() resets state,
//           but keeps edges. The input must be a forest.
// Usage: CentroidDecomposition cd(n); cd.addEdge(u,v); cd.build();
struct CentroidDecomposition {
    int n;
    vector<vector<int>> g;
    vector<int> sub, parent;
    vector<char> dead;

    CentroidDecomposition(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(n, {});
        sub.resize(n);
        parent.assign(n, -1);
        dead.assign(n, false);
    }
    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }

    int sizes(int v, int p) {
        sub[v] = 1;
        for (int u : g[v]) if (u != p && !dead[u]) sub[v] += sizes(u, v);
        return sub[v];
    }
    int centroid(int v, int p, int total) {
        for (int u : g[v])
            if (u != p && !dead[u] && sub[u] > total / 2)
                return centroid(u, v, total);
        return v;
    }
    int decompose(int entry, int p) {
        int c = centroid(entry, -1, sizes(entry, -1));
        parent[c] = p;
        dead[c] = true;
        for (int u : g[c]) if (!dead[u]) decompose(u, c);
        return c;
    }
    void build() {
        fill(dead.begin(), dead.end(), false);
        fill(parent.begin(), parent.end(), -1);
        for (int v = 0; v < n; ++v) if (!dead[v]) decompose(v, -1);
    }
};
