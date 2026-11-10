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
    Lowlink empty(0); empty.build(); assert(empty.bridges.empty());
    mt19937 rng(505);
    for (int it = 0; it < 400; it++) {
        int nn = 1 + rng() % 9;
        int m = rng() % 14;
        vector<pair<int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u = rng() % nn, v = rng() % nn;

            edges.push_back({u, v});
        }
        Lowlink graph(nn);
        for (auto [u, v] : edges) graph.addEdge(u,v);
        graph.build();
        auto first = graph.bridges;
        graph.build();
        assert(graph.bridges == first);

        int base = components(nn, edges, -1);
        for (int v = 0; v < nn; v++) {
            // cutpoint iff removing v increases the component count:
            // C_v = base - 1 + k where v's component splits into k parts
            bool want = components(nn, edges, v) > base;
            assert(graph.is_cut[v] == want);
        }

    }
    return 0;
}
