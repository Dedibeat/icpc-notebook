// Dijkstra shortest paths for nonnegative edge weights.
// Complexity: O((n + m) log n).
// Pitfalls: no negative edges; INF must exceed any possible distance.
// Usage: vector<vector<pair<int,ll>>> g(n); auto d = dijkstra(g, s);
using ll = long long;
const ll INFLL = (1LL << 62);

vector<ll> dijkstra(const vector<vector<pair<int, ll>>>& g, int s) {
    int n = (int)g.size();
    vector<ll> dist(n, INFLL);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) continue;
        for (auto [to, w] : g[v]) {
            if (dist[to] > d + w) {
                dist[to] = d + w;
                pq.push({dist[to], to});
            }
        }
    }
    return dist;
}
