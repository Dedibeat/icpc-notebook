#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/kruskal_reconstruction_tree.cpp"
int main() {
    KruskalTree empty(0,{}), one(1,{});
    assert(empty.roots.empty()); assert(one.roots == vector<int>{0});
    KruskalTree fixed(4, {{10,0,3},{1,0,1},{3,2,3},{2,1,2}});
    assert(fixed.total == 7 && fixed.roots == vector<int>{6});
    assert(fixed.weight[6] == 3);
    mt19937 rng(17);
    const long long INF = LLONG_MAX;
    for (int it = 0; it < 500; ++it) {
        int n = 1+rng()%12;
        vector<KruskalTree::Edge> e;
        vector<vector<long long>> d(n, vector<long long>(n, INF));
        for (int v = 0; v < n; ++v) d[v][v] = LLONG_MIN;
        for (int m = rng()%35; m--; ) {
            int u = rng()%n, v = rng()%n;
            long long w = ((long long)(rng()%11)-5)*1000000000LL;
            e.push_back({w,u,v});
            if (u != v) d[u][v] = d[v][u] = min(d[u][v],w);
        }
        for (int k=0;k<n;++k) for(int u=0;u<n;++u) for(int v=0;v<n;++v)
            d[u][v] = min(d[u][v],max(d[u][k],d[k][v]));
        KruskalTree t(n,e);
        vector<int> p(t.total,-1);
        for (int x=n;x<t.total;++x) for(int u:t.tree[x]) p[u]=x;
        for (int u=0;u<n;++u) for(int v=u+1;v<n;++v) {
            vector<bool> seen(t.total);
            for(int x=u;x!=-1;x=p[x]) seen[x]=true;
            int x=v; while(x!=-1 && !seen[x]) x=p[x];
            if(d[u][v]==INF) assert(x==-1);
            else { assert(x>=n); assert(t.weight[x]==d[u][v]); }
        }
        int roots=0; for(int x=0;x<t.total;++x) roots += p[x]==-1;
        assert(roots == (int)t.roots.size());
        assert(fixed.weight[6] == 3);
    }
}
