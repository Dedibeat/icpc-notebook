// DSU on tree / sack for subtree color counts.
// Fill g[0..n), col[v]. Call dfs_sz(root,-1), then dfs(root,-1,true).
// In dfs(), cnt[c] is the count of color c in subtree(v) at the answer point.
// Time: O(n log n) total for add/remove loops.
const int MAXN = 200000 + 5;
vector<int> g[MAXN];
int col[MAXN], sz[MAXN], st[MAXN], ft[MAXN], ver[MAXN], cnt[MAXN], timer_sack;

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
        cnt[col[ver[i]]] += delta;
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
    cnt[col[v]]++;

    // answer queries for v here, using cnt[color]

    if (!keep) add_subtree(v, -1);
}
