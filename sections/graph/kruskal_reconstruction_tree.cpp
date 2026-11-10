// Kruskal reconstruction forest: leaves [0,n), merge nodes [n,total).
// Build O(m log m + (n+m) log n) time, O(n+m) memory (edges copied).
// weight[LCA(u,v)] is the minimax path value for DISTINCT connected leaves.
// roots lists every component, including isolated vertices; tree stores children.
// Pitfalls: leaves have no edge weight; check connectivity before LCA queries.
// Example: KruskalTree k(3, {{7,0,1}}); // two roots, weight[3]==7
struct KruskalTree {
    struct Edge { long long w; int u, v; };
    int total;
    vector<int> parent, roots;
    vector<vector<int>> tree;
    vector<long long> weight;
    int find(int v) {
        int r = v;
        while (parent[r] != r) r = parent[r];
        while (v != r) { int u = parent[v]; parent[v] = r; v = u; }
        return r;
    }
    KruskalTree(int n, vector<Edge> edges) : total(n), parent(2*n),
        tree(2*n), weight(2*n) {
        iota(parent.begin(), parent.end(), 0);
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.w < b.w; });
        for (auto e : edges) {
            int u = find(e.u), v = find(e.v);
            if (u == v) continue;
            int x = total++;
            weight[x] = e.w;
            tree[x] = {u,v};
            parent[u] = parent[v] = x;
        }
        for (int v = 0; v < total; ++v) if (parent[v] == v) roots.push_back(v);
    }
};
