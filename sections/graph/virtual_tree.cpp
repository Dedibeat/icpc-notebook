// Virtual (auxiliary) tree over a set of key vertices.
// Setup: fill adj[], call dfs(root, root) once. Then vtree(keys) returns key
// vertices plus needed LCAs sorted by tin (first element is the vtree root),
// with vtree edges in vadj[]. Sum of |keys| over all calls: O(K log K) each.
// Pitfalls: vadj is only cleared for returned nodes, so do not read vadj of
// other vertices; recursive dfs on ~2e5 chain needs stack care.
const int MAX_N = 2e5 + 1;
const int LG = 18;

int n, tin[MAX_N], tout[MAX_N], lift[MAX_N][LG], timer;
vector<int> adj[MAX_N], vadj[MAX_N];

void dfs(int v, int p) {
    tin[v] = timer++;
    lift[v][0] = p;
    for (int i = 1; i < LG; i++) lift[v][i] = lift[lift[v][i - 1]][i - 1];
    for (int u : adj[v])
        if (u != p) dfs(u, v);
    tout[v] = timer++;
}

bool is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[v] <= tout[u]; }

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = LG - 1; i >= 0; i--)
        if (!is_ancestor(lift[u][i], v)) u = lift[u][i];
    return lift[u][0];
}

bool sort_tin(const int& a, const int& b) { return tin[a] < tin[b]; }

vector<int> vtree(const vector<int>& key) {
    if (key.empty()) return {};
    vector<int> res = key;
    sort(res.begin(), res.end(), sort_tin);
    int k = res.size();
    for (int i = 1; i < k; i++) res.push_back(lca(res[i - 1], res[i]));
    sort(res.begin(), res.end(), sort_tin);
    res.erase(unique(res.begin(), res.end()), res.end());
    for (int v : res) vadj[v].clear();
    for (int i = 1; i < (int)res.size(); i++)
        vadj[lca(res[i - 1], res[i])].push_back(res[i]);
    return res;
}
