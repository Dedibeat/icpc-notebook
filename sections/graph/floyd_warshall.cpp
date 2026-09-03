// Floyd-Warshall all-pairs shortest paths.
// Complexity: O(n^3) time, O(n^2) memory.
// Pitfalls: guard INF before addition; d[v][v] < 0 means a negative cycle.
// Usage: floyd_warshall(d, INF); initialize diagonal 0 and absent edges INF.
void floyd_warshall(vector<vector<long long>>& d, long long INF) {
    int n = (int)d.size();
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i) if (d[i][k] < INF)
            for (int j = 0; j < n; ++j) if (d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
