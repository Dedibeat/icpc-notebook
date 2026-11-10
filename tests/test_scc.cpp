#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/scc.cpp"

int main() {
    SCC s(6);
    s.addEdge(0, 1);
    s.addEdge(1, 2);
    s.addEdge(2, 0);
    s.addEdge(2, 3);
    s.addEdge(3, 4);
    s.addEdge(4, 3);
    int c = s.build();
    assert(c == 3);
    assert(s.comp[0] == s.comp[1] && s.comp[1] == s.comp[2]);
    assert(s.comp[3] == s.comp[4]);
    assert(s.comp[2] != s.comp[3]);
    assert(s.comp[5] != s.comp[0] && s.comp[5] != s.comp[3]);

    // condensation: deduped DAG edges in topological direction
    auto dag = s.condense(c);
    assert((int)dag.size() == c);
    int edgeCount = 0;
    for (int u = 0; u < c; u++) {
        set<int> uniq(dag[u].begin(), dag[u].end());
        assert(uniq.size() == dag[u].size()); // deduped
        for (int v : dag[u]) {
            assert(u < v); // comp ids are topologically ordered
            edgeCount++;
        }
    }
    set<pair<int, int>> want;
    vector<pair<int, int>> raw = {{0,1},{1,2},{2,0},{2,3},{3,4},{4,3}};
    for (auto [u, v] : raw)
        if (s.comp[u] != s.comp[v]) want.insert({s.comp[u], s.comp[v]});
    assert(edgeCount == (int)want.size());
    assert(s.build() == 3);
    s.addEdge(4, 0);
    assert(s.build() == 2);
    assert(s.comp[0] == s.comp[4]);

    SCC one(1);
    assert(one.build() == 1);
    assert(one.comp[0] == 0);
    SCC empty(0); assert(empty.build() == 0);
    mt19937 rng(77);
    for (int it=0; it<300; ++it) {
        int n=1+rng()%12;
        SCC t(n);
        vector<vector<int>> reach(n, vector<int>(n));
        for(int v=0;v<n;++v) reach[v][v]=1;
        for(int m=rng()%60;m--;) {
            int u=rng()%n,v=rng()%n; t.addEdge(u,v); reach[u][v]=1;
        }
        for(int k=0;k<n;++k) for(int u=0;u<n;++u) for(int v=0;v<n;++v)
            reach[u][v] |= reach[u][k] && reach[k][v];
        int count=t.build(); assert(t.build()==count);
        for(int u=0;u<n;++u) for(int v=0;v<n;++v) {
            assert((t.comp[u]==t.comp[v]) == (reach[u][v] && reach[v][u]));
            if(reach[u][v]) assert(t.comp[u]<=t.comp[v]);
        }
        t.init(1); assert(t.build()==1);
    }
}
