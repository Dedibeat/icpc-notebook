#include <bits/stdc++.h>
 
#define f(k) for(i = 0; i < k; i++)

using namespace std;
 
typedef int l;
 
const int N = 4e5;

l n, m, a, t;
l p[N], w[N], c[N];
 
vector < l > g[N];

l o(l v){
    if(v == p[v]) return v;
    return p[v] = o(p[v]);
}

void d(l v){
    w[v] = 1;
    for(l u : g[v]){
        if(w[u] == 1) t = 1;
        if(!w[u]) d(u);
    }
    w[v] = 2;
}
 
main(){
    l u, v, i;
    cin >> n >> m;
    f(n) p[i] = i;
    f(m)
        cin >> u >> v,
        g[u].push_back(v),
        a += (o(u) != o(v)),
        p[o(u)] = o(v);
    f(n) 
        if(!c[o(i)])
            d(i), c[o(i)] |= t, a += t, t = 0;
    cout << a;
}