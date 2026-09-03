// Functional graph: 64-bit successor jumps plus cycle metadata.
// Complexity: O(n log K) build, O(log K) jump, O(1) metadata queries.
// Pitfalls: next[v] must be valid; dist=0 exactly on a cycle; reset per test.
// Usage: FunctionalGraph f(next); f.go(v,k), f.cycle[v], f.dist[v], f.entry[v].
struct FunctionalGraph {
    static constexpr int LOG = 64;
    vector<vector<int>> up;
    vector<int> cycle, dist, entry;

    FunctionalGraph(const vector<int>& next) {
        int n = (int)next.size();
        up.assign(LOG, vector<int>(n));
        if (n == 0) return;
        up[0] = next;
        for (int b = 1; b < LOG; ++b) for (int v = 0; v < n; ++v)
            up[b][v] = up[b - 1][up[b - 1][v]];

        vector<int> indeg(n), alive(n, 1), order;
        for (int to : next) ++indeg[to];
        queue<int> q;
        for (int v = 0; v < n; ++v) if (!indeg[v]) q.push(v);
        while (!q.empty()) {
            int v = q.front(); q.pop(); alive[v] = 0; order.push_back(v);
            if (--indeg[next[v]] == 0) q.push(next[v]);
        }
        cycle.assign(n, -1); dist.assign(n, -1); entry.assign(n, -1);
        int cid = 0;
        for (int s = 0; s < n; ++s) if (alive[s] && cycle[s] == -1) {
            int v = s;
            do { cycle[v] = cid; dist[v] = 0; entry[v] = v; v = next[v]; } while (v != s);
            ++cid;
        }
        reverse(order.begin(), order.end());
        for (int v : order) {
            int to = next[v];
            cycle[v] = cycle[to]; dist[v] = dist[to] + 1; entry[v] = entry[to];
        }
    }

    int go(int v, unsigned long long k) const {
        for (int b = 0; k; ++b, k >>= 1) if (k & 1) v = up[b][v];
        return v;
    }
};
