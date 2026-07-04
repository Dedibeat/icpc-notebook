#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/bridge.cpp"

int components(int nn, const vector<pair<int, int>>& edges, int skip) {
    vector<vector<int>> g(nn);
    for (int i = 0; i < (int)edges.size(); i++) {
        if (i == skip) continue;
        g[edges[i].first].push_back(edges[i].second);
        g[edges[i].second].push_back(edges[i].first);
    }
    vector<bool> vis(nn);
    int c = 0;
    for (int s = 0; s < nn; s++) if (!vis[s]) {
        c++;
        vector<int> st = {s};
        vis[s] = true;
        while (!st.empty()) {
            int v = st.back(); st.pop_back();
            for (int u : g[v]) if (!vis[u]) { vis[u] = true; st.push_back(u); }
        }
    }
    return c;
}

int main() {
    mt19937 rng(404);
    for (int it = 0; it < 400; it++) {
        int nn = 1 + rng() % 9;
        int m = rng() % 14;
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u = rng() % nn, v = rng() % nn;
            if (u == v) continue; // no self loops
            edges.push_back({u, v}); // duplicates allowed: multiedges
        }
        n = nn;
        adj.assign(nn, {});
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        find_bridges();

        int base = components(nn, edges, -1);
        set<pair<int, int>> got;
        for (auto [u, v] : bridges) got.insert({min(u, v), max(u, v)});
        set<pair<int, int>> want;
        for (int i = 0; i < (int)edges.size(); i++) {
            auto [u, v] = edges[i];
            if (components(nn, edges, i) > base)
                want.insert({min(u, v), max(u, v)});
        }
        assert(got == want);
        assert(bridges.size() == want.size()); // no duplicate reports
    }
    return 0;
}
