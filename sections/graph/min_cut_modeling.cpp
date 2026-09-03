// Maximum-weight closure via one s-t min cut. Depends on Dinic.
// If u is chosen and (u,v) is an implication, v must also be chosen.
// Complexity: one max-flow on n+2 vertices and O(n+m) edges.
// Pitfalls: MCF_INF must exceed total absolute weight; directed implications.
// Usage: auto [best,chosen]=max_weight_closure(weight,implications);
const long long MCF_INF = (1LL<<60);
struct MaxClosureResult { long long value; vector<int> chosen; };

MaxClosureResult max_weight_closure(
    const vector<long long>& weight, const vector<pair<int,int>>& implications) {
    int n=weight.size(), s=n, t=n+1;
    Dinic flow(n+2);
    long long positive=0;
    for (int v=0;v<n;++v) {
        if (weight[v]>0) flow.addEdge(s,v,weight[v]), positive+=weight[v];
        if (weight[v]<0) flow.addEdge(v,t,-weight[v]);
    }
    for (auto [u,v]:implications) flow.addEdge(u,v,MCF_INF);
    long long best=positive-flow.calc(s,t);
    vector<int> chosen;
    for (int v=0;v<n;++v) if (flow.leftOfMinCut(v)) chosen.push_back(v);
    return {best,chosen};
}
