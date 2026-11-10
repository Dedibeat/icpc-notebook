// Centroid decomposition of a tree/forest. Parent[] is the centroid tree.
// Complexity: O(n log n) time, O(n) memory.
// Pitfalls: recursive DFS can overflow on a long chain; build() resets state,
//           but keeps edges. The input must be a forest.
// addEdge loads the forest; build fills parent[v] in the centroid forest
// (a centroid root has parent -1). Walk parent links for centroid-query updates.
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
    void addEdge(int u, int v) {
        g[u].push_back(v); g[v].push_back(u);
    }

    int sizes(int at, int p) {
        sub[at] = 1;
        for (int to : g[at]) if (to != p && !dead[to]) sub[at] += sizes(to, at);
        return sub[at];
    }
    int centroid(int at, int p, int total) {
        for (int to : g[at])
            if (to != p && !dead[to] && sub[to] > total / 2)
                return centroid(to, at, total);
        return at;
    }
    int decompose(int entry, int p) {
        int c = centroid(entry, -1, sizes(entry, -1));
        parent[c] = p;
        dead[c] = true;
        for (int to : g[c]) if (!dead[to]) decompose(to, c);
        return c;
    }
    void build() {
        fill(dead.begin(), dead.end(), false);
        fill(parent.begin(), parent.end(), -1);
        for (int v = 0; v < n; ++v) if (!dead[v]) decompose(v, -1);
    }
};
