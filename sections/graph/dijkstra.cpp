// Dijkstra shortest paths for nonnegative edge weights.
// Complexity: O((n + m) log n).
// Pitfalls: no negative edges. INFLL must exceed all finite shortest paths.
// Usage: vector<vector<pair<int,ll>>> g(n); auto d = dijkstra(g, s);
// Path reconstruction: add vector<int> par(n,-1); set par[to]=at next to
// dist[to]=d+w; walk par[] back from t.
using ll = long long;
const ll INFLL = (1LL << 62);

vector<ll> dijkstra(const vector<vector<pair<int, ll>>>& g, int s) {
    int n = (int)g.size();
    vector<ll> dist(n, INFLL);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, at] = pq.top();
        pq.pop();
        if (d != dist[at]) continue;
        for (auto [to, w] : g[at]) {
            if (w < dist[to] - d) {
                dist[to] = d + w;
                pq.push({dist[to], to});
            }
        }
    }
    return dist;
}
