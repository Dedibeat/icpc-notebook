// Grundy values of a finite DAG; xor values to combine impartial games.
// Complexity: O(n+m) plus mex work bounded by total outdegree.
// Pitfalls: returns {} on a directed cycle; moves must define a finite DAG.
// Usage: auto sg=grundy_dag(moves); answer xor of starting sg values.
vector<int> grundy_dag(const vector<vector<int>>& g) {
    int n = (int)g.size();
    vector<int> sg(n), color(n);
    bool ok = true;
    function<void(int)> dfs = [&](int v) {
        color[v] = 1;
        for (int to : g[v]) {
            if (color[to] == 0) dfs(to);
            else if (color[to] == 1) ok = false;
        }
        vector<int> seen(g[v].size() + 1);
        for (int to : g[v]) if (sg[to] < (int)seen.size()) seen[sg[to]] = 1;
        while (sg[v] < (int)seen.size() && seen[sg[v]]) ++sg[v];
        color[v] = 2;
    };
    for (int v = 0; v < n; ++v) if (!color[v]) dfs(v);
    return ok ? sg : vector<int>{};
}
