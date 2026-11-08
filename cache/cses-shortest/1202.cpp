#include <bits/stdc++.h>
#define P pair<L,L>
using namespace std;
using L=long;
const L N = 1e6, D = 1e9+7;
L n, m, u, v, e, f[N], c[N], p[N], q[N],d;
vector<P> S[N];
 
main()
{
    cin >> n >> m;
    while (m--)
        cin >> u >> v >> e,
        S[u].push_back({v, e});
 
    c[1] = 1;
    priority_queue<P> Q;
    Q.push({0,1});
    while (Q.size()) {
        tie(e,u) = Q.top(); Q.pop();
        if (e == f[u])
            for(auto [v,w] : S[u]) {
                d=f[u]-w;
                L &U=p[v],&T=q[v],&F=f[v];
                if (!F || F < d)
                    Q.push({F=d, v}),
                    c[v] = T = 0,
                    U = N;
 
                if (F == d)
                    (c[v] += c[u]) %= D,
                    U = min(U, p[u] + 1),
                    T = max(T, q[u] + 1);
            }
    }
    cout << -f[n] << ' ' << c[n] << ' ' << p[n] << ' ' << q[n];
}