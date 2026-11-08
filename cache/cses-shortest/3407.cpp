#include <bits/stdc++.h>
using namespace std;
const int mx = 2e5 + 5;

int n, m;

struct edge {
    int u, v, id;
};

map<int, vector<edge>> mp;

int p[mx];

void init() {
    for (int i=0;i<mx;i++) p[i] = i;
}

int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
}

void join(int x, int y) {
    x = find(x); y = find(y);
    p[x] = y;
}

int ans[mx];

signed main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        mp[w].push_back({u, v, i});
    }
    init();
    for (auto [w, vec]:mp) {
        for (auto [u, v, id]:vec) {
            ans[id] = (find(u) != find(v));
        }
        for (auto [u, v, id]:vec) {
            join(u, v);
        }
    }
    for (int i = 1; i <= m; i++) {
        cout << (ans[i] ? "YES" : "NO") << "\n";
    }
}