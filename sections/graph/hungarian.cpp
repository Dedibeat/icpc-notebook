// Minimum-cost assignment: match every row to a distinct column (rows<=cols).
// Complexity: O(rows^2 * cols), memory O(rows+cols).
// Pitfalls: minimizes cost; matrix must be rectangular and rows<=cols;
//           potentials/cost total need long long. Negative costs work.
// Usage: auto [cost,column_of_row]=hungarian(cost_matrix);
pair<long long,vector<int>> hungarian(const vector<vector<long long>>& a) {
    int n=a.size();
    if(!n) return {0,{}};
    int m=a[0].size();
    assert(n<=m && m>0);
    for(auto& row:a) assert((int)row.size()==m);
    const long long INF=(1LL<<62);
    vector<long long>u(n+1),v(m+1),minv(m+1);
    vector<int>p(m+1),way(m+1);
    for(int i=1;i<=n;++i) {
        p[0]=i;
        int j0=0;
        vector<char>used(m+1);
        fill(minv.begin(),minv.end(),INF);
        do {
            used[j0]=1;
            int i0=p[j0],j1=0;
            long long delta=INF;
            for(int j=1;j<=m;++j) if(!used[j]) {
                long long cur=a[i0-1][j-1]-u[i0]-v[j];
                if(cur<minv[j]) minv[j]=cur,way[j]=j0;
                if(minv[j]<delta) delta=minv[j],j1=j;
            }
            for(int j=0;j<=m;++j) {
                if(used[j]) u[p[j]]+=delta,v[j]-=delta;
                else minv[j]-=delta;
            }
            j0=j1;
        } while(p[j0]!=0);
        do {
            int j1=way[j0];p[j0]=p[j1];j0=j1;
        } while(j0);
    }
    vector<int>column(n,-1);
    for(int j=1;j<=m;++j) if(p[j]) column[p[j]-1]=j-1;
    return {-v[0],column};
}
