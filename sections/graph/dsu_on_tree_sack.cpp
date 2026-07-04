// DSU on tree / sack: answer all "subtree of v" queries offline, O(n log n).
// Fill g[0..n) and the marked block, then: dfs_sz(root,-1); dfs(root,-1,true);
// Guarantee: when answer(v) runs, add_one(u,+1) has been applied exactly once
// for every u in subtree(v) and for nothing outside it.
const int MAXN = 200000 + 5;
vector<int> g[MAXN];
int sz[MAXN], st[MAXN], ft[MAXN], ver[MAXN], timer_sack;

// ---- customize: counted state, one vertex in/out, answer hook -------------
int col[MAXN], cnt[MAXN]; // example state: color frequencies
void add_one(int v, int d) { cnt[col[v]] += d; }
void answer(int v) { (void)v; /* record answer for v from current state */ }
// ---- machinery below: do not edit -----------------------------------------

void dfs_sz(int v, int p) {
    st[v] = timer_sack;
    ver[timer_sack++] = v;
    sz[v] = 1;
    for (int u : g[v]) if (u != p) {
        dfs_sz(u, v);
        sz[v] += sz[u];
    }
    ft[v] = timer_sack;
}

void add_subtree(int v, int delta) {
    for (int i = st[v]; i < ft[v]; i++)
        add_one(ver[i], delta);
}

void dfs(int v, int p, bool keep) {
    int bigChild = -1;
    for (int u : g[v])
        if (u != p && (bigChild == -1 || sz[u] > sz[bigChild]))
            bigChild = u;

    for (int u : g[v])
        if (u != p && u != bigChild)
            dfs(u, v, false);

    if (bigChild != -1) dfs(bigChild, v, true);

    for (int u : g[v])
        if (u != p && u != bigChild)
            add_subtree(u, +1);
    add_one(v, +1);

    answer(v);

    if (!keep) add_subtree(v, -1);
}
