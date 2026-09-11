// Find a simple path with k VERTICES, or nullopt if trials found none.
// Directed or undirected adjacency lists; returned path is always valid.
// Time O(trials*2^k*(n+m)); memory O(2^k*n). Intended k<=15 (often much less).
// Miss probability <=(1-k!/k^k)^trials when a k-vertex path exists.
// Usage: colorfulPath(g, 4, 200, rng); nullopt does not prove impossibility.
#include "common.hpp"

optional<vector<int>> colorfulPath(const vector<vector<int>>& g,
                                   int k, int trials, mt19937_64& rng) {
    int n = g.size(); assert(0 <= k && k <= 15 && trials >= 0);
    if (!k) return vector<int>{};
    if (k > n) return nullopt;
    int masks = 1 << k;
    while (trials--) {
        vector<int> color(n);
        for (int& c : color) c = pick(rng, 0, k-1);
        vector<vector<int>> par(masks, vector<int>(n, -2));
        for (int v = 0; v < n; ++v) par[1<<color[v]][v] = -1;
        for (int mask = 1; mask < masks; ++mask)
            for (int v = 0; v < n; ++v) if (par[mask][v] != -2)
                for (int u : g[v]) if (!(mask >> color[u] & 1))
                    par[mask | (1<<color[u])][u] = v;
        for (int v = 0; v < n; ++v) if (par[masks-1][v] != -2) {
            vector<int> path; int mask = masks-1;
            while (v != -1) {
                path.push_back(v); int u = par[mask][v];
                mask ^= 1 << color[v]; v = u;
            }
            reverse(path.begin(), path.end()); return path;
        }
    }
    return nullopt;
}
