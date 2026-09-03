// Bellman-Ford shortest paths with reachable negative-cycle propagation.
// Complexity: O(nm), memory O(n+m).
// Pitfalls: INF/-INF are sentinels; sums are clamped with i128; only cycles
//           reachable from source make neg[v] true.
// Usage: auto r=bellman_ford(n,edges,s); r.dist[v], r.neg[v], r.parent[v].
struct BFEdge { int from,to; long long weight; };
struct BFResult {
    static constexpr long long INF=(1LL<<62);
    vector<long long> dist;
    vector<int> parent;
    vector<char> neg;
};
__extension__ typedef __int128 BFInt;

BFResult bellman_ford(int n,const vector<BFEdge>& edges,int source) {
    const long long INF=BFResult::INF;
    const BFInt WINF=(BFInt)1<<120;
    vector<BFInt>d(n,WINF);
    vector<int>parent(n,-1),changed;
    vector<vector<int>>g(n);
    for(auto e:edges) g[e.from].push_back(e.to);
    d[source]=0;
    for(int it=0;it<n;++it) {
        changed.clear();
        for(auto e:edges) if(d[e.from]!=WINF) {
            BFInt cand=d[e.from]+e.weight;
            if(cand<d[e.to]) d[e.to]=cand,parent[e.to]=e.from,changed.push_back(e.to);
        }
        if(changed.empty()) break;
    }
    vector<char>neg(n);
    queue<int>q;
    for(int v:changed) if(!neg[v]) neg[v]=1,q.push(v);
    while(!q.empty()) {int v=q.front();q.pop();for(int u:g[v])if(!neg[u])neg[u]=1,q.push(u);}
    vector<long long>dist(n,INF);
    for(int v=0;v<n;++v) {
        if(neg[v])dist[v]=-INF;
        else if(d[v]!=WINF)dist[v]=(long long)max((BFInt)-INF,min((BFInt)INF,d[v]));
    }
    return {dist,parent,neg};
}

// Constraints are x[to] - x[from] <= weight. nullopt means infeasible.
optional<vector<long long>> difference_constraints(int n,const vector<BFEdge>& constraints) {
    vector<BFInt>x(n);
    for(int it=0;it<n;++it) {
        bool changed=false;
        for(auto e:constraints) {
            BFInt value=x[e.from]+e.weight;
            if(x[e.to]>value) x[e.to]=value,changed=true;
        }
        if(!changed) {
            vector<long long>answer(n);
            for(int v=0;v<n;++v){assert(LLONG_MIN<=x[v]&&x[v]<=LLONG_MAX);answer[v]=(long long)x[v];}
            return answer;
        }
        if(it==n-1) return nullopt;
    }
    vector<long long>answer(n);return answer;
}
