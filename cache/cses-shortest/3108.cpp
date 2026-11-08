#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
main() {
    ll n, k, s = 0;
    cin >> n >> k;
    ll x[n];
    for (ll &e : x) {
        cin >> e; if (e < 0) s += e,e = -e;
    }
    sort(x, x + n);
    priority_queue<pair<ll, ll>> Q;
    Q.push({-s, -1});
    while (k--) {
        auto [t, i] = Q.top(); Q.pop();
        cout << -t << " ";
        if (i == n - 1) continue;
        if (i >= 0) Q.push({t - x[i + 1] + x[i], i + 1});
        Q.push({t - x[i + 1], i + 1});
    }
}
