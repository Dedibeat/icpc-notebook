	#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int MAX_N = 2e5 + 1;
constexpr int LG = 18;
constexpr int MOD = 998244353;

int n, a[MAX_N];
ll dp[MAX_N], ans;
int tin[MAX_N], tout[MAX_N], d[MAX_N], lift[MAX_N][LG], timer;
vector<int> adj[MAX_N], vadj[MAX_N], at_a[MAX_N];

void dfs(int v, int p) {
	at_a[a[v]].push_back(v);
	tin[v] = timer++;

	lift[v][0] = p;
	for (int i = 1; i < LG; i++) { lift[v][i] = lift[lift[v][i - 1]][i - 1]; }

	for (int u : adj[v]) {
		if (u == p) { continue; }
		dfs(u, v);
	}

	tout[v] = timer++;
}

int is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }

int lca(int u, int v) {
	if (is_ancestor(u, v)) { return u; }
	if (is_ancestor(v, u)) { return v; }

	for (int i = LG - 1; i >= 0; i--) {
		if (!is_ancestor(lift[u][i], v)) { u = lift[u][i]; }
	}
	return lift[u][0];
}

bool sort_tin(const int &a, const int &b) { return tin[a] < tin[b]; }

vector<int> vtree(const vector<int> &key) {
	// NOTE: key must be sorted by tin before LCA insertion, or LCAs can be missed.
	if (key.empty()) return {};

	vector<int> res = key;
	sort(res.begin(), res.end(), sort_tin);

	for (int i = 1; i < (int)key.size(); i++) {
		res.push_back(lca(key[i - 1], key[i]));
	}

	sort(res.begin(), res.end(), sort_tin);
	res.erase(unique(res.begin(), res.end()), res.end());

	for (int v : res) { vadj[v].clear(); }

	for (int i = 1; i < (int)res.size(); i++) {
		vadj[lca(res[i - 1], res[i])].push_back(res[i]);
	}

	return res;
}

int main() {
	cin >> n;

	for (int i = 0; i < n; i++) { cin >> a[i]; }

	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0, 0);

	for (int col = 1; col <= n; col++) {
		vector<int> vt = vtree(at_a[col]);
		reverse(vt.begin(), vt.end());

		for (int v : vt) {
			dp[v] = 1;
			for (int u : vadj[v]) {
				dp[v] *= (dp[u] + 1);
				dp[v] %= MOD;
			}
			if (a[v] != col) { dp[v]--; }

			ans += dp[v];
			ans %= MOD;
			if (a[v] != col) {
				for (int u : vadj[v]) {
					ans += MOD - dp[u];
					ans %= MOD;
				}
			}
		}
	}

	cout << ans << '\n';
}
