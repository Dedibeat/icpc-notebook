#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/bfs_variants.cpp"

int main() {
    vector<vector<int>> g = {{1}, {0, 2}, {1}, {4}, {3}};
    assert((bfs_multi(g, {0, 4, 4}) == vector<int>{0, 1, 2, 1, 0}));
    assert((bfs_multi(g, {}) == vector<int>(5, -1)));

    mt19937 rng(4);
    for (int it = 0; it < 200; ++it) {
        int n = 1 + rng() % 12;
        vector<vector<pair<int, int>>> w(n);
        vector<vector<pair<int, long long>>> normal(n);
        for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) if (rng() % 5 == 0) {
            int c = rng() & 1; w[u].push_back({v, c}); normal[u].push_back({v, c});
        }
        int s = rng() % n;
        auto got = bfs01(w, s);
        const long long INF = 1LL << 62;
        vector<long long> d(n, INF); d[s] = 0;
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [dv, v] = pq.top(); pq.pop(); if (dv != d[v]) continue;
            for (auto [to, c] : normal[v]) if (d[to] > dv + c)
                d[to] = dv + c, pq.push({d[to], to});
        }
        assert(got == d);
    }
}
