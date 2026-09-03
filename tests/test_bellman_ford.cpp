#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/bellman_ford.cpp"

int main(){
    mt19937 rng(30);const long long INF=(1LL<<55);
    for(int n=1;n<=8;++n)for(int it=0;it<500;++it){
        vector<BFEdge>e;vector<vector<long long>>d(n,vector<long long>(n,INF));for(int i=0;i<n;++i)d[i][i]=0;
        for(int u=0;u<n;++u)for(int v=0;v<n;++v)if(rng()%5==0){long long w=(int)(rng()%21)-10;e.push_back({u,v,w});d[u][v]=min(d[u][v],w);}
        for(int k=0;k<n;++k)for(int i=0;i<n;++i)for(int j=0;j<n;++j)if(d[i][k]<INF&&d[k][j]<INF)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        int s=rng()%n;auto got=bellman_ford(n,e,s);
        for(int v=0;v<n;++v){bool neg=false;for(int c=0;c<n;++c)neg|=d[s][c]<INF&&d[c][c]<0&&d[c][v]<INF;assert((bool)got.neg[v]==neg);if(!neg){if(d[s][v]>=INF)assert(got.dist[v]==BFResult::INF);else assert(got.dist[v]==d[s][v]);}}
        auto x=difference_constraints(n,e);bool feasible=true;for(int v=0;v<n;++v)feasible&=d[v][v]>=0;assert((bool)x==feasible);if(x)for(auto z:e)assert((*x)[z.to]<=(*x)[z.from]+z.weight);
    }
}
