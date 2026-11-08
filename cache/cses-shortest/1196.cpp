#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    int n,m,k,a,b,c,i=0;
    cin>>n>>m>>k;
    vector<pair<int,int>> g[n];
    vector<int> s(n,k);
    for(;i++<m;g[a-1].push_back({b-1,c}))
        cin>>a>>b>>c;
    priority_queue<pair<long long,int>> d;
    for(d.push({0,0});d.size();d.pop()){
    auto [w,v]=d.top();
    if(s[v]-->0){
        if(v==n-1)
        cout<<-w<<" ";
        for(auto [i,c]:g[v])
        d.push({w-c,i});
    }
    }
    
}