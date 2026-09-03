// Bitmask DP helpers: submask enumeration and Held-Karp Hamiltonian path.
// Complexity: all submasks of one mask O(2^popcount); Held-Karp O(n^2 2^n).
// Pitfalls: the submask loop includes 0; n must be small (usually <= 20-22);
//           this path starts at 0, visits every vertex, and may end anywhere.
// Usage: for(int s=m;;s=(s-1)&m){... if(!s)break;}  tsp_path(cost);
vector<int> submasks(int mask) {
    vector<int> out;
    for(int s=mask;;s=(s-1)&mask) {
        out.push_back(s);
        if(!s) break;
    }
    return out;
}

long long tsp_path(const vector<vector<long long>>& cost) {
    int n=cost.size();
    if(!n) return 0;
    const long long INF=(1LL<<62);
    vector<vector<long long>> dp(1<<n,vector<long long>(n,INF));
    dp[1][0]=0;
    for(int mask=1;mask<(1<<n);++mask) for(int v=0;v<n;++v) if(mask>>v&1) {
        if(dp[mask][v]==INF) continue;
        for(int u=0;u<n;++u) if(!(mask>>u&1))
            dp[mask|1<<u][u]=min(dp[mask|1<<u][u],dp[mask][v]+cost[v][u]);
    }
    return *min_element(dp.back().begin(),dp.back().end());
}
