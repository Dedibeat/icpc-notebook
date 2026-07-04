// Eulerian path/circuit starting at src; returns node sequence (nedges+1
// nodes) or {} if none exists FROM src. Works for directed and undirected.
// gr[u] holds {v, edge_id}. Directed: push once. Undirected: push both
// directions with the SAME edge id. Ids must be 0..nedges-1.
// For a circuit pick any src with an edge; for a path start at an odd-degree
// (undirected) / out-in=1 (directed) vertex. Graph edges must be connected.
// Source: KACTL EulerWalk. Time: O(V + E). Iterative, no stack issues.
vector<int> eulerWalk(vector<vector<pair<int, int>>>& gr, int nedges, int src = 0) {
    int n = gr.size();
    vector<int> D(n), its(n), eu(nedges), ret, s = {src};
    D[src]++; // to allow Euler paths, not just cycles
    while (!s.empty()) {
        int x = s.back(), y, e, &it = its[x], end = gr[x].size();
        if (it == end) { ret.push_back(x); s.pop_back(); continue; }
        tie(y, e) = gr[x][it++];
        if (!eu[e]) {
            D[x]--, D[y]++;
            eu[e] = 1;
            s.push_back(y);
        }
    }
    for (int x : D) if (x < 0 || (int)ret.size() != nedges + 1) return {};
    return {ret.rbegin(), ret.rend()};
}
