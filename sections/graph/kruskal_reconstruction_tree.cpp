// Kruskal reconstruction tree for an undirected weighted graph.
// Original vertices are [0, n0). New internal node weight is edge weight.
// For connected graph, root is total_nodes - 1 after build().
// Time: O(m log m alpha(n)).
const int MAXK = 400000 + 5; // at least 2 * original_n + m_components
struct KEdge { int w, u, v; };
vector<KEdge> edges;
vector<int> ktree[MAXK];
int dsu[MAXK], node_weight[MAXK], total_nodes;

int getRoot(int u) {
    if (u == dsu[u]) return u;
    return dsu[u] = getRoot(dsu[u]);
}

int build_kruskal_tree(int n0) {
    total_nodes = n0;
    for (int i = 0; i < MAXK; i++) {
        dsu[i] = i;
        ktree[i].clear();
    }
    sort(edges.begin(), edges.end(), [](const KEdge& a, const KEdge& b) {
        return a.w < b.w;
    });
    for (auto e : edges) {
        int u = getRoot(e.u), v = getRoot(e.v);
        if (u == v) continue;
        int x = total_nodes++;
        node_weight[x] = e.w;
        ktree[x].push_back(u);
        ktree[x].push_back(v);
        dsu[u] = dsu[v] = dsu[x] = x;
    }
    return total_nodes - 1;
}
