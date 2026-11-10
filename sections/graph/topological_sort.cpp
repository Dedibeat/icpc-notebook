// Topological order: each edge u->v puts u before v. O(n+m) time, O(n) space.
// Pitfalls: recursive depth O(n); empty result means cycle or empty graph.
// Usage: auto order=topological_sort(g); bool dag=order.size()==g.size();
vector<int> topological_sort(const vector<vector<int>>& g) {
    vector<int> state(g.size()), order; // 0=unseen, 1=active, 2=finished
    auto dfs = [&](auto&& self, int at) -> bool {
        if (state[at]) return state[at] == 2;
        state[at] = 1;
        for (int to : g[at]) if (!self(self, to)) return false;
        state[at] = 2;
        order.push_back(at);
        return true;
    };
    for (int v = 0; v < (int)g.size(); ++v)
        if (!dfs(dfs, v)) return {};
    reverse(order.begin(), order.end());
    return order;
}
