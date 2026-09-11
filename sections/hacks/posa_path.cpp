// Hamiltonian PATH heuristic for simple UNDIRECTED graphs; nullopt = not found.
// Time O(restarts*(steps+1)*n), memory O(n); steps counts extensions/rotations.
// A found path is valid; there is no general success/time guarantee.
// Reverse suffix after a pivot adjacent to endpoint. Cycles need an extra check.
// Usage: posaPath(g, 50, 20*g.size(), rng); adjacency must be symmetric.
#include "common.hpp"

optional<vector<int>> posaPath(const vector<vector<int>>& g,
                               int restarts, int steps, mt19937_64& rng) {
    int n = g.size(); assert(restarts >= 0 && steps >= 0);
    if (!n) return vector<int>{};
    while (restarts--) {
        vector<int> path{(int)pick(rng, 0, n-1)}, pos(n, -1);
        pos[path[0]] = 0;
        for (int it = 0; ; ++it) {
            if ((int)path.size() == n) return path;
            if (it == steps) break;
            int last = path.back(); vector<int> next, pivots;
            for (int u : g[last]) {
                if (pos[u] == -1) next.push_back(u);
                else if (pos[u]+2 < (int)path.size())
                    pivots.push_back(pos[u]);
            }
            if (!next.empty()) {
                int u = next[pick(rng, 0, next.size()-1)];
                pos[u] = path.size(); path.push_back(u);
            } else if (!pivots.empty()) {
                int p = pivots[pick(rng, 0, pivots.size()-1)];
                reverse(path.begin()+p+1, path.end());
                for (int i = p+1; i < (int)path.size(); ++i) pos[path[i]] = i;
            } else break;
        }
    }
    return nullopt;
}
