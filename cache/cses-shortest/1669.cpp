#include <bits/stdc++.h>
using namespace std;
 
#define i int
#define M '   '
#define b push_back
 
i p[M], x, y, k;
vector<i> g[M], s;
 
i f(i w, i r) {
    p[w] = r;
 
    for (i u: g[w])
        if (u - r) { 
            if (p[u]) {
                s.b(u), s.b(w);
                while (w - u)
                    w = p[w], s.b(w);
 
                cout << size(s);
                for (i j: s) cout << ' ' << j;
                exit(0);
            }
            f(u, w);    
        }
}
 
main() {
    cin >> x >> y;
    while (cin >> x >> y)
        g[x].b(y), g[y].b(x);
 
    while (++k < M)
        if (!p[k]) 
            f(k, M);
 
    cout << "IMPOSSIBLE";
}