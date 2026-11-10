#pragma once
// Bridges and articulation points of an undirected multigraph.
// O(n+m) time and memory. addEdge returns an edge ID; build resets results.
// bridges contains edge IDs; is_cut[v] marks articulation points.
// Pitfalls: insert each edge once; DFS recursion can overflow on long chains.
// Example: Lowlink g(3); g.addEdge(0,1); g.addEdge(1,2); g.build();
// Then g.bridges has both IDs and g.is_cut[1] is true.
struct Lowlink {
    int n, timer = 0, edges = 0;
    vector<vector<pair<int,int>>> adj;
    vector<int> tin, low, bridges;
    vector<bool> is_cut;
    Lowlink(int n) : n(n), adj(n) {}
    int addEdge(int u, int v) {
        adj[u].push_back({v, edges});
        adj[v].push_back({u, edges});
        return edges++;
    }
    void dfs(int v, int parent_edge = -1) {
        tin[v] = low[v] = timer++;
        int children = 0;
        for (auto [u, id] : adj[v]) {
            if (id == parent_edge) continue;
            if (tin[u] != -1) low[v] = min(low[v], tin[u]);
            else {
                dfs(u, id);
                low[v] = min(low[v], low[u]);
                if (low[u] > tin[v]) bridges.push_back(id);
                if (parent_edge != -1 && low[u] >= tin[v]) is_cut[v] = true;
                ++children;
            }
        }
        if (parent_edge == -1) is_cut[v] = children > 1;
    }
    void build() {
        timer = 0;
        bridges.clear();
        tin.assign(n, -1);
        low.resize(n);
        is_cut.assign(n, false);
        for (int v = 0; v < n; ++v) if (tin[v] == -1) dfs(v);
    }
};
