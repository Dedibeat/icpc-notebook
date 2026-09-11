// Find a vertex cover of size <=k, or nullopt if none exists (EXACT).
// Time O(2^k*(n+m)), stack/copies O((k+1)*(n+m)) for nonnegative k.
// Simple undirected graph: no loops/parallel edges (degree rule requires this).
// All state is local, so repeated calls are independent. k is a small budget.
// Usage: vertexCover(3, {{0,1},{1,2}}, 1) returns {1}.
#include "common.hpp"

optional<vector<int>> vertexCover(int n, vector<pair<int,int>> edges, int k) {
    vector<int> chosen;
    function<bool(const vector<pair<int,int>>&,int)> dfs =
    [&](const vector<pair<int,int>>& e, int left) {
        if (left < 0) return false;
        if (e.empty()) return true;
        if (!left) return false;
        vector<int> degree(n);
        for (auto [u,v] : e) { ++degree[u]; ++degree[v]; }
        int forced = max_element(degree.begin(), degree.end())-degree.begin();
        vector<int> branch{e[0].first, e[0].second};
        if (degree[forced] > left) branch = {forced};
        for (int v : branch) {
            vector<pair<int,int>> next;
            for (auto [a,b] : e)
                if (a != v && b != v) next.push_back({a,b});
            chosen.push_back(v);
            if (dfs(next, left-1)) return true;
            chosen.pop_back();
        }
        return false;
    };
    if (dfs(edges, k)) return chosen;
    return nullopt;
}
