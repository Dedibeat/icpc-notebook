// Strongly connected components, Kosaraju.
// Complexity: O(n + m).
// Pitfalls: comp ids are topological order of SCC DAG sources to sinks.
// Usage: SCC s(n); s.addEdge(u,v); int c = s.build(); s.comp[v] in [0,c).
struct SCC {
    int n;
    vector<vector<int>> g, rg;
    vector<int> comp;
    SCC(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(n, {});
        rg.assign(n, {});
        comp.assign(n, -1);
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    int build() {
        vector<int> order, vis(n);
        function<void(int)> dfs1 = [&](int v) {
            vis[v] = 1;
            for (int to : g[v]) if (!vis[to]) dfs1(to);
            order.push_back(v);
        };
        function<void(int, int)> dfs2 = [&](int v, int c) {
            comp[v] = c;
            for (int to : rg[v]) if (comp[to] == -1) dfs2(to, c);
        };
        for (int i = 0; i < n; i++) if (!vis[i]) dfs1(i);
        reverse(order.begin(), order.end());
        int cnt = 0;
        for (int v : order) if (comp[v] == -1) dfs2(v, cnt++);
        return cnt;
    }
};
