#include <bits/stdc++.h>
using namespace std;

bool e[16][16], p[16];
int n, c[16], K;

void dfs(const int i, const int k) {
	if (i == n) {
		cout << k << '\n';
		for (int j = 0; j < n; j++) cout << c[j] + 1 << ' ';
		exit(0);
	}
	bool ds[k] = {};
	for (int j = 0; j < i; j++) if (e[i][j]) ds[c[j]] = true;
	for (c[i] = 0; c[i] < k; c[i]++) {
		if (!ds[c[i]]) dfs(i + 1, k);
	}
	if (k == K) return;
	c[i] = k;
	dfs(i + 1, k + 1);
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int m;
	cin >> n >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		--a; --b;
		e[a][b] = e[b][a] = true;
	}
	iota(p, p + n, 0);
	random_shuffle(p, p + n);
	while (++K) dfs(0, 0);
}