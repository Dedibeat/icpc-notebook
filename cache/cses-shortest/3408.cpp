#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node {
	int x, y, w, fx, fy;
} a[200007];
int n, m, k, cnt, ans, pos = 1, sum, tmp, opt, mx = -1e9, x, y, q, f, w;
map <int, vector<int>> v;
struct dsu {
	unordered_map<int, int>fa;
	int find (int x) {
		return !fa[x] ? x : (fa[x] = find (fa[x]) );
	}
	bool merge (int x, int y) {
		x = find (x), y = find (y);
		if (x == y) return 0;
		fa[x] = y;
		return 1;
	}
} g;
signed main() {
	cin >> n >> m >> q;
	for (int i = 1; i <= m; i++) {
		scanf ("%lld%lld%lld", &x, &y, &w), a[i] = {x, y, w};
		v[w].push_back (i);
	}
	for (auto [i, _] : v) {
		for (int j : v[i]) a[j].fx = g.find (a[j].x), a[j].fy = g.find (a[j].y);
		for (int j : v[i]) g.merge (a[j].fx, a[j].fy);
	}
	for (int i = 1; i <= q; i++) {
		scanf ("%lld", &k), f = 1;
		dsu t;
		for (int j = 1; j <= k; j++) {
			scanf ("%lld", &x);
			if (!t.merge (a[x].fx, a[x].fy) ) f = 0;
		}
		if (f) printf ("YES\n");
		else printf ("NO\n");
	}
	return 0;
}