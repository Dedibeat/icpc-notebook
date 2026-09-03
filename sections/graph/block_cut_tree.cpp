// Vertex-biconnected components and block-cut forest of an undirected graph.
// Original vertices are 0..n-1; block nodes are n..n+blocks.size()-1.
// Complexity: O(n+m) plus sorting vertices inside blocks, O(n+m) memory.
// Pitfalls: use edge ids (parallel edges work); self-loops are not supported;
//           recursive DFS can overflow. Isolated vertices stay isolated.
// Usage: BlockCutTree bc(n); bc.addEdge(u,v); bc.build();
struct BlockCutTree {
    int n, timer;
    vector<pair<int,int>> edges;
    vector<vector<pair<int,int>>> g;
    vector<int> tin, low, edgeStack;
    vector<vector<int>> blocks, tree;

    BlockCutTree(int n = 0) { init(n); }
    void init(int n_) {
        n=n_; timer=0; edges.clear(); g.assign(n,{});
        tin.assign(n,-1); low.resize(n); edgeStack.clear();
        blocks.clear(); tree.clear();
    }
    int addEdge(int u,int v) {
        int id=edges.size(); edges.push_back({u,v});
        g[u].push_back({v,id}); g[v].push_back({u,id});
        return id;
    }
    void makeBlock(int lastEdge) {
        vector<int> vertices;
        while (true) {
            int id=edgeStack.back(); edgeStack.pop_back();
            vertices.push_back(edges[id].first);
            vertices.push_back(edges[id].second);
            if (id==lastEdge) break;
        }
        sort(vertices.begin(),vertices.end());
        vertices.erase(unique(vertices.begin(),vertices.end()),vertices.end());
        blocks.push_back(vertices);
    }
    void dfs(int v,int parentEdge) {
        tin[v]=low[v]=timer++;
        for (auto [u,id]:g[v]) {
            if (id==parentEdge) continue;
            if (tin[u]==-1) {
                edgeStack.push_back(id); dfs(u,id);
                low[v]=min(low[v],low[u]);
                if (low[u]>=tin[v]) makeBlock(id);
            } else if (tin[u]<tin[v]) {
                edgeStack.push_back(id);
                low[v]=min(low[v],tin[u]);
            }
        }
    }
    void build() {
        timer=0; fill(tin.begin(),tin.end(),-1); edgeStack.clear(); blocks.clear();
        for (int v=0;v<n;++v) if (tin[v]==-1) dfs(v,-1);
        tree.assign(n+blocks.size(),{});
        for (int b=0;b<(int)blocks.size();++b) for (int v:blocks[b]) {
            tree[n+b].push_back(v); tree[v].push_back(n+b);
        }
    }
};
