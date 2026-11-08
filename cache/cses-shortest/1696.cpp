#import <bits/stdc++.h>

using namespace std;

int n, m, c, p, k, M[501];
vector<int> G[501], V;

int d(int u) {
    if (!V[u]++) for (int v : G[u]) if (!M[v] || d(M[v])) return M[v] = u;
    return 0;
}

main() {
    for (cin >> n >> m >> k; cin >> c >> k;) G[c].push_back(k);

    for (;n--;V.assign(501, 0), p+=d(n+1)>0);
    for (cout << p << " "; n++ < m;) if (M[n]) cout << M[n] << " " << n << " ";
}