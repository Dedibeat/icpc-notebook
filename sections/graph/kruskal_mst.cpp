// Kruskal minimum spanning forest; requires the notebook DSU snippet.
// Complexity: O(m log m + m alpha(n)).
// Pitfalls: disconnected input returns a forest; connected iff used == n-1.
// Usage: auto [weight,used]=kruskal_mst(n,edges);
struct MSTEdge { int u, v; long long w; };

pair<long long, int> kruskal_mst(int n, vector<MSTEdge> edges) {
    sort(edges.begin(), edges.end(), [](const MSTEdge& a, const MSTEdge& b) {
        return a.w < b.w;
    });
    DSU dsu(n);
    long long weight = 0;
    int used = 0;
    for (auto e : edges) if (dsu.unite(e.u, e.v)) weight += e.w, ++used;
    return {weight, used};
}
