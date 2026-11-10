// Multi-source BFS and 0-1 BFS shortest paths.
// Complexity: O(n+m); -1/INF means unreachable.
// Pitfalls: 0-1 BFS requires every edge weight to be exactly 0 or 1.
// Usage: bfs_multi(g,sources); bfs01(weighted_graph,source);
vector<int> bfs_multi(const vector<vector<int>>& g, const vector<int>& sources) {
    vector<int> d(g.size(), -1);
    queue<int> q;
    for (int s : sources) if (0 <= s && s < (int)g.size() && d[s] == -1)
        d[s] = 0, q.push(s);
    while (!q.empty()) {
        int at = q.front(); q.pop();
        for (int to : g[at]) if (d[to] == -1) d[to] = d[at] + 1, q.push(to);
    }
    return d;
}

vector<long long> bfs01(const vector<vector<pair<int, int>>>& g, int s) {
    const long long INF = (1LL << 62);
    vector<long long> d(g.size(), INF);
    deque<pair<long long, int>> q;
    d[s] = 0; q.push_front({0, s});
    while (!q.empty()) {
        auto [distAt, at] = q.front(); q.pop_front();
        if (distAt != d[at]) continue;
        for (auto [to, w] : g[at]) if (d[to] > distAt + w) {
            d[to] = distAt + w;
            if (w == 0) q.push_front({d[to], to});
            else q.push_back({d[to], to});
        }
    }
    return d;
}
