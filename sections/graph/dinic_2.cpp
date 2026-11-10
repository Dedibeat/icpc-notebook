// Dinic maximum flow with capacity scaling. addEdge(u,v,c,rc) adds residual
// capacities in both directions; calc augments the current residual network.
// Use distinct terminals for min-cut queries. calc(s,s) returns zero.
// Afterwards leftOfMinCut(v) marks the source side and minCutEdges lists its
// original crossing arcs. Example: addEdge(0,1,5); calc(0,1)==5.
// Unit capacities: O(min(sqrt(E),V^(2/3))*E); bipartite matching O(sqrt(V)*E).
// Requires bits/stdc++.h and using namespace std.
using ll = long long;
using vi = vector<int>;
#ifndef sz
#define sz(x) (int)(x).size()
#endif
#ifndef rep
#define rep(i,a,b) for (int i = (a); i < (b); ++i)
#endif

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		int i = sz(adj[a]), j = sz(adj[b]);
		adj[a].push_back({b, j + (a == b), c, c});
		adj[b].push_back({a, i, rcap, rcap});
	}
	ll dfs(int at, int t, ll f) {
		if (at == t || !f) return f;
		for (int& i = ptr[at]; i < sz(adj[at]); i++) {
			Edge& e = adj[at][i];
			if (lvl[e.to] == lvl[at] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		if (s == t) return 0;
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int at = q[qi++];
				for (Edge e : adj[at])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[at] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) {
		return lvl[a] != 0;
	}
	vector<pair<int, int>> minCutEdges() {
		vector<pair<int, int>> cut;
		rep(at,0,sz(adj)) if (leftOfMinCut(at)) {
			for (Edge& e : adj[at])
				if (e.oc > 0 && e.c == 0 && !leftOfMinCut(e.to))
					cut.push_back({at, e.to});
		}
		return cut;
	}
};
