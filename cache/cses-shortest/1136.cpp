#include <bits/stdc++.h>
using namespace std;

#define I int
#define l for (i = 
I n, m, x, y, a, t, i = 0, c['   '], f['   '], g['   '], U['   '][18];
set<I> G['   '];

void D(I u, I p=1) {
    f[u] = t++;
    U[u][0] = p;
    for (i = 1; i < 18; i++) U[u][i] = U[U[u][i-1]][i-1];
    for (I v : G[u])
        if (v-p) D(v, u), c[u] += c[v];
    
    g[u] = t;
}

main() {
    cin >> n >> m;
    l 1; i < n; i++) cin >> x >> y, G[x].insert(y), G[y].insert(x);

    #define A(u,v) (f[u] <= f[v] && g[u] >= g[v])

    for (D(1); cin >> x >> y; c[a]--) {
        c[x]++; c[y]++; 

        if (A(x,y)) a = x;
        else if (A(y,x)) a = y;
        else {
            l 17; i >= 0; i--)
                if (!A(U[x][i], y)) x = U[x][i];
            a = U[x][0];
        }
        if (U[a][0] ^ a) c[U[a][0]]--;
    }

    D(1);
    l 1; i <= n;) cout << c[i++] << " ";
}