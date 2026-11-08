#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {

    ll n, m, o = 1, i = 0;
    cin >> n >> m;
    vector<vector<pair<ll,ll>>> a(n + 1);
    vector<ll> v(n + 1), p(n + 1);

    function<void(ll)> d = [&](ll u) {
        v[u] = 1;
        for (auto [x, y] : a[u]) {
            if (!v[x]) 
                p[x] = p[u] + y, d(x);
            else if (p[x] != p[u] + y) 
                o = 0;
            if (!o)
                return;
        } 
    };

    while (m--) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        a[u].push_back({v, w});
        a[v].push_back({u, -w});
    }

    for (; i <= n; i++) 
        if (!v[i]) 
            d(i);

    if (!o) 
        cout << "NO";
    else {
    cout << "YES\n";
    for (i = 1; i <= n; i++) 
        cout << p[i] - p[i - 1] << ' ';
    }
}
