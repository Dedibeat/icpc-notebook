#include <bits/stdc++.h>
using namespace std;
#define i int
i main() {
    i n, m, k, a, b; cin >> n >> m >> k;
    queue<array<i, 3>> q;
    while (k--) cin >> a, q.push({--a, a, 0});
    vector<vector<i>> g(n), s(n);
    while (m--) cin >> a >> b, g[--a].push_back(--b), g[b].push_back(a);
    vector<i> t(n, -1);
    while (q.size()) {
        auto [u, o, d] = q.front();
        q.pop();
        if (size(s[u]) > 1) continue;
        if (size(s[u]) && s[u][0] == o) continue;
        s[u].push_back(o);
        if (u != o && t[u] == -1) t[u] = d;
        for (i v : g[u]) q.push({v, o, d + 1});
    }
    for (i x : t) cout << x << ' ';
}
