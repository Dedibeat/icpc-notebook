#include <bits/stdc++.h>
#define p insert
#define I int
#define N [(I)2e5]
using namespace std;
I n, x, y, T N, D N;
set<I> e N;
set<pair<I,I>> a;

#define d(x,y) (a.p({x,y}),D[x]^=1)

void r(I u,I p){
 T[u]=++x;
 for(I v:e[u]){
 if(!T[v])r(v,u),D[v]?d(v,u):d(u,v);
 else if(v-p&&T[v]<T[u])d(u,v);
 }
}

I main(){
 for(cin>>n>>x;cin>>x>>y;e[x].p(y))e[y].p(x);
 for (;n;n--)if(!T[n]){
 r(n,0);
 if (D[n])cout<<"IMPOSSIBLE",exit(0);
 }
 for(auto[x,y]:a)cout<<x<<" "<<y<<"\n";
}