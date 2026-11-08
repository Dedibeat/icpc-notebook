#include <bits/stdc++.h>
#define K(i,r) for(I i=1; i<=r; ++i)
#define I int
#define P pair<I, I>
#define e cin>>
#define g cout<<
using namespace std;
const I M = 5e3, Z = 2e9;
I n, m, s, t, o, y, b, z, x, A[M], U[M], C[M], T[M], l[M], f[M], q[M];
vector<P> S[M];

void E(I u, I v, I c, I w) {
    A[++m] = w;
    C[m] = c;
    S[u].emplace_back(v, m);
    S[v].emplace_back(u, -m);
}

I F() {
    queue<I> Q;
    fill(f + 1, f + o + 1, Z);
    f[s] = 0;
    Q.push(s);
    q[s] = 1;
    while (Q.size()) {
        I u = Q.front(); Q.pop();
        q[u] = 0;
        for(P eg : S[u]) {
            I v = eg.first, Y = eg.second, c;
            if (Y > 0) {
                if (U[Y] == A[Y]) continue;
                c = f[u] - C[Y];
            }
            else {
                if (!U[-Y]) continue;
                c = f[u] + C[-Y];
            }
            if (f[v] > c) {
                f[v] = c;
                T[v] = u;
                l[v] = Y;
                if (!q[v]) Q.push(v), q[v] = 1;
            }
        }
    }
    return f[t] != Z;
}

I main()
{
    e n;
    o = n * 2 + 2;
    s = o - 1;
    t = o;
    K(i, n) {
        e x;
        y += x;
        E(s, i, 0, x);
    }
    K(i, n) {
        e x;
        z += x;
        E(i + n, t, 0, x);
    }
    if (y != z) return g -1, 0;
    K(i, n) K(j, n) {
        e x;
        E(i, j+n, x, 1);
    }
    while (F()) {
        for(I u = t, Y; u != s; u = T[u]) {
            Y = l[u];
            if (Y > 0) b += C[Y], ++U[Y];
            else b -= C[-Y], --U[-Y];
        }
        --y;
    }
    if (y) return g -1, 0;
    g b;
    K(i, n) {
        g '\n';
        K(j, n)
            g (U[i*n+j+n] ? 'X' : '.');
    }
}
