// Rerooting DP. Configured to compute sum of distances from every vertex.
// To reuse, edit ONLY DP/ID and merge/addEdge/addRoot in the marked block.
// Complexity: O(n) time and memory for constant-time DP operations.
// Pitfalls: merge must be associative; recursive DFS can overflow; tree only.
// Usage: Rerooting rr(g); vector<DP> answer=rr.solve(0);
struct Rerooting {
    // ---- customize the DP -------------------------------------------------
    struct DP { long long size, sum; };
    static DP id() { return {0,0}; }
    static DP merge(DP a,DP b) { return {a.size+b.size,a.sum+b.sum}; }
    static DP addEdge(DP a,int /*from*/,int /*to*/) { return {a.size,a.sum+a.size}; }
    static DP addRoot(DP a,int /*v*/) { ++a.size; return a; }
    // ----------------------------------------------------------------------

    int n;
    const vector<vector<int>>& g;
    vector<DP> down, answer;
    Rerooting(const vector<vector<int>>& graph):n(graph.size()),g(graph),down(n),answer(n){}

    DP dfsDown(int v,int p) {
        DP cur=id();
        for (int u:g[v]) if (u!=p) cur=merge(cur,addEdge(dfsDown(u,v),u,v));
        return down[v]=addRoot(cur,v);
    }
    void dfsAll(int v,int p,DP fromParent) {
        int d=g[v].size();
        vector<DP> side(d),pre(d+1,id()),suf(d+1,id());
        for (int i=0;i<d;++i) {
            int u=g[v][i];
            side[i]=(u==p?fromParent:addEdge(down[u],u,v));
            pre[i+1]=merge(pre[i],side[i]);
        }
        for (int i=d-1;i>=0;--i) suf[i]=merge(side[i],suf[i+1]);
        answer[v]=addRoot(pre[d],v);
        for (int i=0;i<d;++i) if (g[v][i]!=p) {
            DP without=addRoot(merge(pre[i],suf[i+1]),v);
            dfsAll(g[v][i],v,addEdge(without,v,g[v][i]));
        }
    }
    vector<DP> solve(int root=0) {
        if (!n) return {};
        dfsDown(root,-1); dfsAll(root,-1,id());
        return answer;
    }
};
