#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/dsu.cpp"
#include "../sections/graph/lca_binary_lifting.cpp"
#include "../sections/graph/block_cut_tree.cpp"
#include "../sections/graph/block_cut_tree_example.cpp"

void check(int n, const vector<pair<int,int>>& edges) {
    vector<vector<int>> g(n);
    ostringstream input, want;
    input << n << ' ' << edges.size() << ' ' << n*n*n << '\n';
    for(auto [u,v]:edges) {
        input << u << ' ' << v << '\n';
        g[u].push_back(v); g[v].push_back(u);
    }
    for(int u=0;u<n;++u) for(int v=0;v<n;++v) for(int x=0;x<n;++x) {
        input << u << ' ' << v << ' ' << x << '\n';
        vector<bool> seen(n);
        queue<int> q;
        if(u!=x) { seen[u]=true; q.push(u); }
        while(!q.empty()) {
            int at=q.front(); q.pop();
            for(int to:g[at]) if(to!=x && !seen[to]) {
                seen[to]=true; q.push(to);
            }
        }
        want << (seen[v] ? "YES\n" : "NO\n");
    }
    istringstream in(input.str()); ostringstream out;
    auto oldin=cin.rdbuf(in.rdbuf()); auto oldout=cout.rdbuf(out.rdbuf());
    solve_vertex_removal();
    cin.rdbuf(oldin); cout.rdbuf(oldout);
    assert(out.str()==want.str());
}
int main() {
    check(0,{});
    check(1,{});
    check(5,{{0,1},{1,2},{2,0},{2,3}}); // printed graph, including isolate 4
    check(4,{{0,1},{0,1},{1,2}}); // parallel edge, bridge, isolate
    check(4,{{0,1},{1,2},{2,3},{3,0}}); // one block
    check(5,{{0,1},{1,2},{2,3},{3,4}}); // chain
    mt19937 rng(82);
    for(int it=0;it<300;++it) {
        int n=1+rng()%9;
        vector<pair<int,int>> edges;
        for(int u=0;u<n;++u) for(int v=u+1;v<n;++v) if(rng()%4==0) {
            edges.push_back({u,v});
            if(rng()%4==0) edges.push_back({u,v});
        }
        check(n,edges); // all (u,v,x), including equal endpoints and repeated calls
    }
}
