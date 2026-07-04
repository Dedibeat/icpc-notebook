#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/lca_binary_lifting.cpp"
#include "../sections/graph/virtual_tree.cpp"

int main() {
    // fixed example
    {
        LCA T(7);
        T.addEdge(0, 1);
        T.addEdge(0, 2);
        T.addEdge(1, 3);
        T.addEdge(1, 4);
        T.addEdge(2, 5);
        T.addEdge(2, 6);
        T.build(0);

        vector<pair<int, int>> edges;
        vector<int> nodes = vtree({5, 3, 4}, T, edges);
        vector<int> expect = {0, 1, 3, 4, 5};
        sort(expect.begin(), expect.end(), [&](int a, int b) { return T.tin[a] < T.tin[b]; });
        assert(nodes == expect);
        set<pair<int, int>> es(edges.begin(), edges.end());
        assert(es == (set<pair<int, int>>{{0, 1}, {0, 5}, {1, 3}, {1, 4}}));

        nodes = vtree({4}, T, edges);
        assert(nodes == vector<int>{4} && edges.empty());
        assert(vtree({}, T, edges).empty());
    }

    // randomized: parent of x in vtree = deepest closure node strictly above x
    mt19937 rng(9090);
    for (int it = 0; it < 300; it++) {
        int n = 2 + rng() % 40;
        LCA T(n);
        vector<int> par(n, -1);
        for (int v = 1; v < n; v++) {
            par[v] = rng() % v;
            T.addEdge(par[v], v);
        }
        T.build(0);

        int k = 1 + rng() % min(6, n); // cannot request more keys than vertices
        set<int> keyset;
        while ((int)keyset.size() < k) keyset.insert(rng() % n);
        vector<int> keys(keyset.begin(), keyset.end());

        vector<pair<int, int>> edges;
        vector<int> nodes = vtree(keys, T, edges);

        // closure = keys + pairwise LCAs
        set<int> closure(keys.begin(), keys.end());
        for (int a : keys) for (int b : keys) closure.insert(T.lca(a, b));
        assert((int)nodes.size() == (int)closure.size());
        for (int x : nodes) assert(closure.count(x));
        // nodes sorted by tin; front is the shallowest (root)
        for (int i = 1; i < (int)nodes.size(); i++)
            assert(T.tin[nodes[i - 1]] < T.tin[nodes[i]]);

        map<int, int> vpar;
        for (auto [p, c] : edges) {
            assert(!vpar.count(c)); // each child has one parent
            vpar[c] = p;
        }
        assert((int)edges.size() == (int)nodes.size() - 1);
        for (int x : closure) {
            // expected parent: deepest proper ancestor of x in closure
            int best = -1;
            for (int y : closure) {
                if (y == x) continue;
                if (T.lca(x, y) == y && (best == -1 || T.depth[y] > T.depth[best]))
                    best = y;
            }
            if (best == -1) assert(!vpar.count(x)); // root
            else assert(vpar.count(x) && vpar[x] == best);
        }
    }
    return 0;
}
