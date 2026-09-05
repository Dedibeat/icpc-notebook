#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/topological_sort.cpp"

int main() {
    vector<vector<int>> g = {{1, 2}, {3}, {3}, {}};
    auto p = topological_sort(g);
    vector<int> at(4);
    for (int i = 0; i < 4; ++i) at[p[i]] = i;
    for (int v = 0; v < 4; ++v) for (int to : g[v]) assert(at[v] < at[to]);
    assert(topological_sort(vector<vector<int>>{{1}, {0}}).empty());
    assert(topological_sort({}).empty());
    vector<vector<int>> parallel = {{1, 1}, {}};
    assert(topological_sort(parallel).size() == 2);
    assert(topological_sort({{0}}).empty());
    assert(topological_sort({{}, {2}, {1}}).empty());
    mt19937 rng(18);
    for (int n=1;n<=30;++n) for(int it=0;it<100;++it) {
        vector<vector<int>> g(n);
        vector<int> indeg(n);
        for(int v=0;v<n;++v) for(int u=0;u<n;++u)
            if(rng()%30==0) { g[v].push_back(u); ++indeg[u]; }
        queue<int> q;
        for(int v=0;v<n;++v) if(!indeg[v]) q.push(v);
        int count=0;
        while(!q.empty()) {
            int v=q.front(); q.pop(); ++count;
            for(int u:g[v]) if(!--indeg[u]) q.push(u);
        }
        auto order=topological_sort(g);
        assert((order.size()==g.size()) == (count==n));
        if(count==n) {
            vector<int> pos(n,-1);
            for(int i=0;i<n;++i) { assert(pos[order[i]]==-1); pos[order[i]]=i; }
            for(int v=0;v<n;++v) for(int u:g[v]) assert(pos[v]<pos[u]);
        }
    }
}
