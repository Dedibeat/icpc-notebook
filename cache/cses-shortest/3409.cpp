#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> E(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        E[i] = {w, u, v};
    }
    auto SE = E;
    sort(SE.begin(), SE.end());
    vector<int> p(n + 1), we(n + 1, INT_MAX), siz(n + 1, 1);
    iota(p.begin(), p.end(), 0);
    ll cst = 0;
    for (auto [w, u, v] : SE) {
        while (u != p[u])
            u = p[u];
        while (v != p[v])
            v = p[v];
        if (u == v)
            continue;
        cst += w;
        if (siz[u] > siz[v])
            swap(u, v);
        p[u] = v;
        we[u] = w;
        siz[v] += siz[u];
    }
    for (int i = 0; i < m; i++) {
        auto [w, u, v] = E[i];
        while (p[u] != v && p[v] != u) {
            if (we[u] < we[v])
                u = p[u];
            else
                v = p[v];
        }
        cout << cst + w - (p[u] == v ? we[u] : we[v]) << '\n';
    }
}