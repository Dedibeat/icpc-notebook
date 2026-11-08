#include <bits/stdc++.h>
#define sz(x) x.size()
#define pb push_back
using namespace std;using ll=uint64_t;using vi=vector<int>;
ll th(vector<vi>&g,int u,int p=-1){ll id=1;
for(int v:g[u])if(v!=p)id*=th(g,v,u);
return id+100003;}
int f(vector<vi>&g,int u,int p,vi&c){int ok=1,nn=1,n=sz(g)-1;
for(int v:g[u])if(v!=p){int t=f(g,v,u,c);
if(t>n/2)ok=0;
nn+=t;}
if(ok&&n-nn<=(n/2))c.pb(u);
return nn;}
int cc(vector<vi>&j,vector<vi>&k){vi c1,c2;f(j,1,-1,c1);f(k,1,-1,c2);
if(sz(c1)!=sz(c2))return 0;
for(int c:c2)if(th(k, c)==th(j,c1[0]))return 1;
return 0;}
int main(){int T,n,u,v;cin>>T;while(T--){
cin>>n;vector<vi>j(n+1),k(n+1);
for(int i=1;i<n;++i)cin>>u>>v,j[u].pb(v),j[v].pb(u);
for(int i=1;i<n;++i)cin>>u>>v,k[u].pb(v),k[v].pb(u);
cout<<(cc(j,k)?"YES\n":"NO\n");}}
