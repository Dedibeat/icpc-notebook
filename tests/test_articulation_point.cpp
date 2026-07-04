#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/articulation_point.cpp"

int components(int nn, const vector<pair<int, int>>& edges, int skipVertex) {
    vector<vector<int>> g(nn);
    for (auto [u, v] : edges) {
        if (u == skipVertex || v == skipVertex) continue;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<bool> vis(nn);
    if (skipVertex >= 0) vis[skipVertex] = true;
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
    mt19937 rng(505);
    for (int it = 0; it < 400; it++) {
        int nn = 2 + rng() % 8;
        int m = rng() % 14;
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u = rng() % nn, v = rng() % nn;
            if (u == v) continue;
            edges.push_back({u, v});
        }
        n = nn;
        adj.assign(nn, {});
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        find_cutpoints();

        int base = components(nn, edges, -1);
        for (int v = 0; v < nn; v++) {
            // cutpoint iff removing v increases the component count:
            // C_v = base - 1 + k where v's component splits into k parts
            bool want = !adj[v].empty() && components(nn, edges, v) > base;
            assert(is_cut[v] == want);
        }
        // cutpoints list matches flags, sorted unique
        vector<int> expect;
        for (int v = 0; v < nn; v++) if (is_cut[v]) expect.push_back(v);
        assert(cutpoints == expect);
    }
    return 0;
}
