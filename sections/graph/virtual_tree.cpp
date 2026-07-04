// Virtual (auxiliary) tree over key vertices.
// Requires LCA from lca_binary_lifting.cpp, built on the tree.
// Returns key vertices plus needed LCAs sorted by tin (front = root of the
// virtual tree) and fills edges as (parent, child) pairs. O(k log k) per call.
// Typical DP: process returned nodes in reverse (children before parents).
vector<int> vtree(vector<int> v, LCA& T, vector<pair<int, int>>& edges) {
    edges.clear();
    if (v.empty()) return {};
    auto byTin = [&](int a, int b) { return T.tin[a] < T.tin[b]; };
    sort(v.begin(), v.end(), byTin);
    int k = v.size();
    for (int i = 1; i < k; i++) v.push_back(T.lca(v[i - 1], v[i]));
    sort(v.begin(), v.end(), byTin);
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i < (int)v.size(); i++)
        edges.push_back({T.lca(v[i - 1], v[i]), v[i]});
    return v;
}
