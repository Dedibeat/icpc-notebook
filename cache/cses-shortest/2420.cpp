#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int N, M;
	cin >> N >> M;
	char S[N + 1], Z[N + 1];
	for (int i = 1; i <= N; i++) {
		cin >> S[i];
		Z[N - i] = S[i];
	}
	while (M--) {
		int o;
		cin >> o;
		if (o == 1) {
			int k;
			cin >> k >> S[k];
			Z[N - k] = S[k];
		}
		else {
			int l, r;
			cin >> l >> r;
			cout << (memcmp(S + l, Z + N - r, (r - l + 1) / 2) ? "NO" : "YES") << '\n';
		}
	}
}



