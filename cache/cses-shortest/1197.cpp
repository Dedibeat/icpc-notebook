#include <bits/stdc++.h>
using namespace std;
long long n,m,a,b,c,p[2501],k[2501];
int l(int u,int v)
{   
    if(u==v){
        cout<<"YES\n"<<v<<" ";
        return v;
    }
    if(v=(u?l(p[u],v):u))
    cout<<u<<" ";
    return v;
}
int main()
{
    cin>>n>>m;
    vector<pair<int, int>> g[n+1];
    for(;m--;g[a].push_back({b,c}))
    cin>>a>>b>>c;
    for(b=1;b--;)
        for(int u=0;u++<n;)
            for(auto [v,d]:g[u])
                if(k[v]>k[u]+d){
                    k[v] = k[u] + d;
                    p[v]=u;
                    b=1;
                    if(l(u,v)){
                        cout<<v;
                        return 0;
                    }
                }
    cout<<"NO";
}