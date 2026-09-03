// Kahn topological sort; empty result means a cycle (or an empty graph).
// Complexity: O(n+m).
// Pitfalls: parallel edges each contribute to indegree; check size for cycles.
// Usage: auto order=topological_sort(g); bool dag=order.size()==g.size();
vector<int> topological_sort(const vector<vector<int>>& g) {
    vector<int> indeg(g.size());
    for (auto& e : g) for (int to : e) ++indeg[to];
    queue<int> q;
    for (int i = 0; i < (int)g.size(); ++i) if (!indeg[i]) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int v = q.front(); q.pop(); order.push_back(v);
        for (int to : g[v]) if (--indeg[to] == 0) q.push(to);
    }
    if (order.size() != g.size()) return {};
    return order;
}
