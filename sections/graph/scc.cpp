// Strongly connected components, Kosaraju.
// Complexity: O(n + m); condense() O(m log m).
// Comp ids are in topological order (every edge has comp[u] <= comp[v]),
// so DP over the DAG can just loop components in id order.
// addEdge loads arcs; build fills comp[v] and returns the component count;
// condense(count) returns the deduplicated component DAG.
// Example: edges 0->1,1->0,1->2 give build()==2, comp[0]==comp[1],
//          comp[1]<comp[2].
struct SCC {
    int n;
    vector<vector<int>> g, rg;
    vector<int> comp;
    SCC(int n = 0) {
        init(n);
    }
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
    vector<vector<int>> condense(int c) {
        vector<vector<int>> dag(c);
        set<pair<int, int>> seen;
        for (int u = 0; u < n; u++)
            for (int v : g[u])
                if (comp[u] != comp[v] && seen.insert({comp[u], comp[v]}).second)
                    dag[comp[u]].push_back(comp[v]);
        return dag;
    }
};
