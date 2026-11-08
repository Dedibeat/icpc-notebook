#include <bits/stdc++.h>
using namespace std;

vector<int> a[100005];
int c[100005], r[100005];
int i, n, u, f, v;

void p(int v){
    vector<int> l = {v};
    n = v;

    do {
        n = r[n];
        l.push_back(n);
        f++;
    } while(n != v);

    cout<<f+1<<"\n";
    for(i=f; i>=0; i--) cout<<l[i]<<" ";
}

void d(int u){
    c[u] = 1;

    for(int v : a[u]){
        r[v] = u;

        if(!c[v])
            d(v);
        else if(c[v] == 1 && !f)
            p(v);
    }

    c[u] = 2;
}

main () {
    for(cin>>n>>v; cin>>u>>v;) a[u].push_back(v);
    while(++i <= n) if(!c[i]) d(i);
    if(!f) cout<<"IMPOSSIBLE";
}