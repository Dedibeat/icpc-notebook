// Min-cost flow with potentials. Negative costs ok; no negative cost cycles.
// Source: Stanford/KACTL successive shortest path style.
// Complexity: O(F E log V), plus O(VE) Bellman-Ford init.
// Pitfalls: costs/caps are long long; minCost(s,t,need) may send < need flow.
// Usage: MCMF mf(n); mf.addEdge(u,v,cap,cost); auto [flow,cost]=mf.minCost(s,t,need);
struct MCMF {
    using ll = long long;
    const ll INF = (1LL << 62);
    struct Edge {
        int to, rev;
        ll cap, cost;
    };
    int n;
    vector<vector<Edge>> g;
    vector<ll> pot, dist;
    vector<int> pv, pe;

    MCMF(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(n, {});
        pot.assign(n, 0);
        dist.resize(n);
        pv.resize(n);
        pe.resize(n);
    }
    void addEdge(int v, int to, ll cap, ll cost) {
        if (cap <= 0) return;
        Edge a{to, (int)g[to].size(), cap, cost};
        Edge b{v, (int)g[v].size(), 0, -cost};
        g[v].push_back(a);
        g[to].push_back(b);
    }
    void setPotentials(int s) {
        fill(pot.begin(), pot.end(), INF);
        pot[s] = 0;
        for (int it = 0; it < n - 1; it++) {
            bool changed = false;
            for (int v = 0; v < n; v++) if (pot[v] != INF) {
                for (Edge& e : g[v]) if (e.cap && pot[e.to] > pot[v] + e.cost) {
                    pot[e.to] = pot[v] + e.cost;
                    changed = true;
                }
            }
            if (!changed) break;
        }
        for (ll& x : pot) if (x == INF) x = 0;
    }
    pair<ll, ll> minCost(int s, int t, ll need = (1LL << 62)) {
        setPotentials(s);
        ll flow = 0, cost = 0;
        while (flow < need) {
            fill(dist.begin(), dist.end(), INF);
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            dist[s] = 0;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (d != dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    Edge& e = g[v][i];
                    if (!e.cap) continue;
                    ll nd = d + e.cost + pot[v] - pot[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int v = 0; v < n; v++) if (dist[v] != INF) pot[v] += dist[v];
            ll add = need - flow;
            for (int v = t; v != s; v = pv[v]) add = min(add, g[pv[v]][pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                Edge& e = g[pv[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
                cost += add * e.cost;
            }
            flow += add;
        }
        return {flow, cost};
    }
};
