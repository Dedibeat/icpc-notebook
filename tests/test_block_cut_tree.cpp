#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/block_cut_tree.cpp"

int main() {
    BlockCutTree bc(8);
    bc.addEdge(0,1); bc.addEdge(1,2); bc.addEdge(2,0);
    bc.addEdge(2,3); bc.addEdge(3,4); bc.addEdge(3,4);
    bc.addEdge(5,6); // vertex 7 is isolated
    bc.build();
    vector<vector<int>> blocks=bc.blocks;
    for(auto& b:blocks) sort(b.begin(),b.end());
    sort(blocks.begin(),blocks.end());
    vector<vector<int>> want={{0,1,2},{2,3},{3,4},{5,6}};
    sort(want.begin(),want.end());
    assert(blocks==want);
    for(auto [u,v]:bc.edges) {
        bool together=false;
        for(auto& b:bc.blocks) together|=find(b.begin(),b.end(),u)!=b.end() && find(b.begin(),b.end(),v)!=b.end();
        assert(together);
    }
    int edges=0; for(auto& x:bc.tree) edges+=x.size(); edges/=2;
    vector<char> seen(bc.tree.size()); int components=0;
    for(int s=0;s<(int)seen.size();++s) if(!seen[s]) {
        ++components; queue<int> q; q.push(s); seen[s]=1;
        while(!q.empty()){int v=q.front();q.pop();for(int u:bc.tree[v])if(!seen[u])seen[u]=1,q.push(u);}
    }
    assert(edges==(int)bc.tree.size()-components);
}
