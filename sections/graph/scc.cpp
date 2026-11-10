// Strongly connected components, Kosaraju.
// Pitfall: recursive DFS can overflow the stack on long chains.
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
    vector<int> comp, order, vis;
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
    void dfs1(int v) {
        vis[v] = 1;
        for (int u : g[v]) if (!vis[u]) dfs1(u);
        order.push_back(v);
    }
    void dfs2(int v, int c) {
        comp[v] = c;
        for (int u : rg[v]) if (comp[u] == -1) dfs2(u, c);
    }
    int build() {
        fill(comp.begin(), comp.end(), -1);
        order.clear();
        vis.assign(n, 0);
        for (int i = 0; i < n; i++) if (!vis[i]) dfs1(i);
        reverse(order.begin(), order.end());
        int cnt = 0;
        for (int v : order) if (comp[v] == -1) dfs2(v, cnt++);
        return cnt;
    }
    vector<vector<int>> condense(int c) {
        vector<vector<int>> dag(c);
        set<pair<int, int>> seen;
        for (int at = 0; at < n; at++)
            for (int to : g[at])
                if (comp[at] != comp[to] && seen.insert({comp[at], comp[to]}).second)
                    dag[comp[at]].push_back(comp[to]);
        return dag;
    }
};
