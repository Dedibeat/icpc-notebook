#include<bits/stdc++.h>
using namespace std;
#define N 60005
bitset<N>b[N];vector<int>g[N];int u[N],n,m,x,y,i;
void d(int v){
    if(!u[v]++){
    for(int t:g[v])d(t),b[v]|=b[t];
    b[v][v]=1;
    }
}
main(){
    for(cin>>n>>m;cin>>x>>y;g[x].push_back(y));
    for(;i<n;d(++i),cout<<b[i].count()<<' ');
}