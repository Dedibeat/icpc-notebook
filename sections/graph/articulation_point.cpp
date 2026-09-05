// Articulation points of an undirected graph. Fill n and adj, call
// find_cutpoints(); result: is_cut[v] flags + `cutpoints` list (no dups).
// Handles disconnected graphs. O(n + m).
// Pitfalls: recursive dfs (~2e5 depth); root is a cutpoint iff children > 1.
int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> visited, is_cut;
vector<int> tin, low, cutpoints;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p != -1)
                is_cut[v] = true;
            ++children;
        }
    }
    if (p == -1 && children > 1)
        is_cut[v] = true;
}

void find_cutpoints() { // Resets globals and fills is_cut/cutpoints for the current graph.
    timer = 0;
    visited.assign(n, false);
    is_cut.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    cutpoints.clear();
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
    for (int i = 0; i < n; ++i)
        if (is_cut[i]) cutpoints.push_back(i);
}
