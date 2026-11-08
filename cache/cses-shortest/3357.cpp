#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u);
    }
    vector d(2, vector(n, vector<int> (n, 2e9)));
    for (int i = 0; i < n; i++) {
        queue<pair<int, int>> q;
        q.push({i, d[0][i][i] = 0});
        while (q.size()) {
            auto [u, c] = q.front();
            q.pop();
            for (int v : g[u]) {
                if (d[c ^ 1][i][v] > d[c][i][u] + 1) {
                    q.push({v, c ^ 1});
                    d[c ^ 1][i][v] = d[c][i][u] + 1;
                }
            }
        }
    }
    while (q--) {
        int u, v, x;
        cin >> u >> v >> x;
        cout << (d[x & 1][--u][--v] <= x ? "YES" : "NO") << '\n';
    }
    return 0;
}
