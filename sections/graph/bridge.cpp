// Bridges of an undirected graph. Fill n and adj, call find_bridges();
// result is in `bridges`. Handles multiedges (a doubled edge is no bridge)
// and disconnected graphs. O(n + m).
// Pitfalls: recursive dfs (~2e5 depth); store each parallel edge separately.
int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<pair<int, int>> bridges;
vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (int to : adj[v]) {
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                bridges.push_back({v, to});
        }
    }
}

void find_bridges() { // Resets globals and fills bridges for the current undirected graph.
    timer = 0;
    bridges.clear();
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}
