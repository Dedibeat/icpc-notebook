// DSU on tree / sack: answer all "subtree of v" queries offline, O(n log n).
// Per test: init_sack(n); fill g/col; dfs_sz(root,-1); dfs(root,-1,false);
// keep=false at the root undoes every add_one, so the counted state ends
// empty and init_sack costs only O(previous n). Storage O(MAXN).
// Pitfalls: vertices and colors in [0,MAXN); recursive DFS.
// Guarantee: when answer(v) runs, add_one(u,+1) has been applied exactly once
// for every u in subtree(v) and for nothing outside it.
const int MAXN = 200000 + 5;
vector<int> g[MAXN];
int sz[MAXN], st[MAXN], ft[MAXN], ver[MAXN], timer_sack, sack_n;

// ---- customize: counted state, one vertex in/out, answer hook -------------
int col[MAXN], freq[MAXN]; // example state: color frequencies
void add_one(int v, int d) { freq[col[v]] += d; }
void answer(int v) { (void)v; /* record answer for v from current state */ }
// ---- machinery below: do not edit -----------------------------------------
void init_sack(int n) { // call BEFORE loading each test case
    for (int i = 0; i < sack_n; ++i) g[i].clear();
    sack_n = n, timer_sack = 0;
}
void dfs_sz(int at, int p) {
    st[at] = timer_sack;
    ver[timer_sack++] = at;
    sz[at] = 1;
    for (int to : g[at]) if (to != p) dfs_sz(to, at), sz[at] += sz[to];
    ft[at] = timer_sack;
}
void add_subtree(int v, int d) {
    for (int i = st[v]; i < ft[v]; i++) add_one(ver[i], d);
}
void dfs(int at, int p, bool keep) {
    int big = -1;
    for (int to : g[at]) if (to != p && (big == -1 || sz[to] > sz[big])) big = to;
    for (int to : g[at]) if (to != p && to != big) dfs(to, at, false);
    if (big != -1) dfs(big, at, true);
    for (int to : g[at]) if (to != p && to != big) add_subtree(to, +1);
    add_one(at, +1);
    answer(at);
    if (!keep) add_subtree(at, -1);
}
