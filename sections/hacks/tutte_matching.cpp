// Maximum matching SIZE of an undirected graph, via randomized Tutte rank.
// Time O(trials*n^3), memory O(n^2); answer is always a lower bound.
// Failure <= (n/HMOD)^trials for independent uniform field samples, n<HMOD.
// Vertices 0..n-1; no loops. Parallel input edges are harmless. No edge recovery.
// Usage: tutteSize(3, {{0,1},{1,2},{2,0}}, 3, rng) == 1 with high probability.
#include "common.hpp"

int tutteSize(int n, const vector<pair<int,int>>& edges,
              int trials, mt19937_64& rng) {
    assert(n >= 0 && n < HMOD && trials > 0);
    int best = 0;
    while (trials--) {
        vector<vector<ll>> a(n, vector<ll>(n));
        for (auto [u,v] : edges) {
            assert(0 <= u && u < n && 0 <= v && v < n && u != v);
            ll r = pick(rng, 0, HMOD-1);
            a[u][v] = r; a[v][u] = hnorm(-r);
        }
        int rank = 0;
        for (int col = 0; col < n; ++col) {
            int row = rank;
            while (row < n && !a[row][col]) ++row;
            if (row == n) continue;
            swap(a[row], a[rank]);
            ll inv = hpow(a[rank][col], HMOD-2);
            for (int i = rank+1; i < n; ++i) {
                ll f = a[i][col]*inv % HMOD;
                for (int j = col; j < n; ++j)
                    a[i][j] = hnorm(a[i][j] - f*a[rank][j]%HMOD);
            }
            ++rank;
        }
        assert(rank % 2 == 0);
        best = max(best, rank/2);
    }
    return best;
}
