// DSU on tree / sack: answer all "subtree of v" queries offline, O(n log n).
// Call init_sack(), fill g/col and the marked block, then for a nonempty tree:
// dfs_sz(root,-1); dfs(root,-1,true);
// Pitfalls: colors in [0,MAXN); recursive DFS; keep=true leaves counts filled.
// init_sack costs O(MAXN + old edges); storage O(MAXN).
// Guarantee: when answer(v) runs, add_one(u,+1) has been applied exactly once
// for every u in subtree(v) and for nothing outside it.
const int MAXN = 200000 + 5;
vector<int> g[MAXN];
int sz[MAXN], st[MAXN], ft[MAXN], ver[MAXN], timer_sack;

// ---- customize: counted state, one vertex in/out, answer hook -------------
int col[MAXN], cnt[MAXN]; // example state: color frequencies
void add_one(int v, int d) { cnt[col[v]] += d; }
void answer(int v) { (void)v; /* record answer for v from current state */ }
// Call BEFORE loading each test case; reset any extra custom state here too.
void init_sack() {
    timer_sack = 0;
    for (int i = 0; i < MAXN; ++i) g[i].clear();
    fill(cnt, cnt + MAXN, 0);
}
// ---- machinery below: do not edit -----------------------------------------

void dfs_sz(int at, int p) {
    st[at] = timer_sack;
    ver[timer_sack++] = at;
    sz[at] = 1;
    for (int to : g[at]) if (to != p) {
        dfs_sz(to, at);
        sz[at] += sz[to];
    }
    ft[at] = timer_sack;
}

void add_subtree(int v, int delta) {
    for (int i = st[v]; i < ft[v]; i++)
        add_one(ver[i], delta);
}

void dfs(int at, int p, bool keep) {
    int bigChild = -1;
    for (int to : g[at])
        if (to != p && (bigChild == -1 || sz[to] > sz[bigChild]))
            bigChild = to;

    for (int to : g[at])
        if (to != p && to != bigChild)
            dfs(to, at, false);

    if (bigChild != -1) dfs(bigChild, at, true);

    for (int to : g[at])
        if (to != p && to != bigChild)
            add_subtree(to, +1);
    add_one(at, +1);

    answer(at);

    if (!keep) add_subtree(at, -1);
}
