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
        int at = s.back(), to, e, &it = its[at], end = gr[at].size();
        if (it == end) { ret.push_back(at); s.pop_back(); continue; }
        tie(to, e) = gr[at][it++];
        if (!eu[e]) {
            D[at]--, D[to]++;
            eu[e] = 1;
            s.push_back(to);
        }
    }
    for (int x : D) if (x < 0 || (int)ret.size() != nedges + 1) return {};
    return {ret.rbegin(), ret.rend()};
}
