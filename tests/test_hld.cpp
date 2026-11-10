#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/heavy_light_decomposition.cpp"

template<bool Edges>
void check(const vector<vector<int>>& g, mt19937& rng) {
    int n = g.size();
    HLD<Edges> h(g);
    if (!n) return;

    vector<int> parent(n, -1), depth(n), byPos(n, -1);
    vector<int> pending{0};
    while (!pending.empty()) {
        int v = pending.back();
        pending.pop_back();
        for (int u : g[v]) if (u != parent[v]) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            pending.push_back(u);
        }
    }
    for (int v = 0; v < n; ++v) {
        assert(0 <= h.pos[v] && h.pos[v] < n);
        assert(byPos[h.pos[v]] == -1);
        byPos[h.pos[v]] = v;
    }

    for (int q = 0; q < 100; ++q) {
        int u = rng() % n, v = rng() % n;
        if (q == 0) v = u;
        vector<int> got, want;
        h.process(u, v, [&](int l, int r) {
            assert(0 <= l && l <= r && r <= n);
            got.insert(got.end(), byPos.begin() + l, byPos.begin() + r);
        });
        while (u != v) {
            if (depth[u] < depth[v]) swap(u, v);
            want.push_back(u);
            u = parent[u];
        }
        if (!Edges) want.push_back(u);
        sort(want.begin(), want.end());
        sort(got.begin(), got.end());
        assert(got == want);
    }

    for (int v = 0; v < n; ++v) {
        auto [l, r] = h.subtree(v);
        assert(0 <= l && l <= r && r <= n);
        vector<int> got(byPos.begin() + l, byPos.begin() + r), want;
        for (int u = 0; u < n; ++u) {
            if (Edges && u == v) continue;
            int a = u;
            while (a != -1 && a != v) a = parent[a];
            if (a == v) want.push_back(u);
        }
        sort(got.begin(), got.end());
        assert(got == want);
    }
}

int main() {
    mt19937 rng(2026);
    check<false>({}, rng);
    check<true>({}, rng);
    check<false>({{}}, rng);
    check<true>({{}}, rng);
    for (int it = 0; it < 60; ++it) {
        int n = 2 + rng() % 30;
        vector<vector<int>> g(n);
        for (int v = 1; v < n; ++v) {
            int p = rng() % v;
            g[p].push_back(v);
            g[v].push_back(p);
        }
        check<false>(g, rng);
        check<true>(g, rng);
    }
}
