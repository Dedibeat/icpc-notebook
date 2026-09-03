#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/offline_dynamic_connectivity.cpp"

bool brute(int n,const set<pair<int,int>>& edges,int s,int t) {
    vector<vector<int>> g(n); for (auto [u,v]:edges) g[u].push_back(v),g[v].push_back(u);
    vector<char> seen(n); queue<int> q; q.push(s); seen[s]=1;
    while (!q.empty()) { int v=q.front();q.pop(); for(int u:g[v]) if(!seen[u]) seen[u]=1,q.push(u); }
    return seen[t];
}
int main() {
    mt19937 rng(12);
    for (int it=0;it<200;++it) {
        int n=1+rng()%8;
        OfflineDynamicConnectivity dc(n);
        set<pair<int,int>> active;
        vector<char> want;
        for (int step=0;step<100;++step) {
            int u=rng()%n,v=rng()%n; if(u>v)swap(u,v);
            auto e=make_pair(u,v);
            int type=rng()%3;
            if(type==0 && !active.count(e)) active.insert(e),dc.addEdge(u,v);
            else if(type==1 && active.count(e)) active.erase(e),dc.removeEdge(u,v);
            else want.push_back(brute(n,active,u,v)),dc.connected(u,v);
        }
        assert(dc.solve()==want);
    }
}
