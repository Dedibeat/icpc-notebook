#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using iiii = tuple <int, int, int, int>;

const int inf = 1e9 + 8;

int P[1000];
ll D[1000];
int n, m, k;
vector <iiii> vex;

void bfs() {
    D[0] = 0;
    fill(D + 1, D + n, inf);
    
    for (int _ = 1; _ < n; ++_)
        for (int i = 0; i < vex.size(); ++i) {
            auto [u, v, p, h] = vex[i];
            if (p && D[v] > D[u] + h) {
                P[v] = i;
                D[v] = D[u] + h;
            }
        }
    
    return ;
}

int dfs(int n, int k) {
    if (n == 0) return k;
    
    auto &[u1, v1, p1, h1] = vex[P[n]];
    auto &[u2, v2, p2, h2] = vex[P[n] ^ 1];
    
    int rx = dfs(u1, min(p1, k));
    p1 -= rx;
    p2 += rx;
    
    return rx;
}

int main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    cin >> n >> m >> k;
    
    int u, v, p, h;
    while (m--) {
        cin >> u >> v >> p >> h;
        vex.emplace_back(u -= 1, v -= 1, p, h);
        vex.emplace_back(v, u, 0, -h);
    }
    
    ll mx = 0;
    while (k) {
        bfs();
        if (D[n - 1] == inf) return cout << -1, 0;
        
        int rx = dfs(n - 1, k);
        mx += D[n - 1] * rx;
        k -= rx;
    }
    
    cout << mx;
    
    
    return 0;
}