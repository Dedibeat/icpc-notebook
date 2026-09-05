// Offline add/remove-edge connectivity using a rollback DSU.
// Complexity: O(q log q log n) time, O(q log q + n) memory.
// Input: append add/remove/connected events; every call advances time.
// Effect: each edge is active on [add time,remove time); no duplicate active copy.
// Output: connected returns an answer index; solve returns answers by that index.
// Pitfalls: every removal must match one active insertion.
struct RollbackDSU {
    vector<int> p, sz;
    vector<pair<int, int>> history; // attached root, old size of its parent

    RollbackDSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n); iota(p.begin(), p.end(), 0);
        sz.assign(n, 1); history.clear();
    }
    int find(int v) const { while (v != p[v]) v = p[v]; return v; }
    bool same(int a, int b) const { return find(a) == find(b); }
    int snapshot() const { return history.size(); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) { history.push_back({-1, -1}); return false; }
        if (sz[a] < sz[b]) swap(a, b);
        history.push_back({b, sz[a]});
        p[b] = a; sz[a] += sz[b];
        return true;
    }
    void rollback(int snap) {
        while ((int)history.size() > snap) {
            auto [b, old] = history.back(); history.pop_back();
            if (b == -1) continue;
            int a = p[b];
            sz[a] = old; p[b] = b;
        }
    }
};

struct OfflineDynamicConnectivity {
    struct Op { char type; int u, v, id; };
    using Edge = pair<int, int>;
    int n, queries = 0;
    vector<Op> ops;
    vector<vector<Edge>> seg;

    OfflineDynamicConnectivity(int n = 0) : n(n) {}
    static Edge edge(int u, int v) { if (u > v) swap(u, v); return {u, v}; }
    void addEdge(int u, int v)    { // Appends an edge insertion at the next time.
        ops.push_back({'+', u, v, -1});
    }
    void removeEdge(int u, int v) { // Appends removal of the currently active edge.
        ops.push_back({'-', u, v, -1});
    }
    int connected(int u, int v) { // Appends a query and returns its answer index.
        ops.push_back({'?', u, v, queries});
        return queries++;
    }
    void addInterval(int x, int l, int r, int ql, int qr, Edge e) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) { seg[x].push_back(e); return; }
        int m = (l + r) / 2;
        addInterval(2*x, l, m, ql, qr, e);
        addInterval(2*x+1, m, r, ql, qr, e);
    }
    void dfs(int x, int l, int r, RollbackDSU& dsu, vector<char>& ans) {
        int snap = dsu.snapshot();
        for (auto [u, v] : seg[x]) dsu.unite(u, v);
        if (r - l == 1) {
            if (ops[l].type == '?') ans[ops[l].id] = dsu.same(ops[l].u, ops[l].v);
        } else {
            int m = (l + r) / 2;
            dfs(2*x, l, m, dsu, ans);
            dfs(2*x+1, m, r, dsu, ans);
        }
        dsu.rollback(snap);
    }
    vector<char> solve() {
        int q = ops.size();
        vector<char> ans(queries);
        if (!q) return ans;
        seg.assign(4*q, {});
        map<Edge, int> active;
        for (int t = 0; t < q; ++t) {
            Edge e = edge(ops[t].u, ops[t].v);
            if (ops[t].type == '+') {
                assert(!active.count(e));
                active[e] = t;
            }
            if (ops[t].type == '-') {
                assert(active.count(e));
                addInterval(1, 0, q, active[e], t, e);
                active.erase(e);
            }
        }
        for (auto [e, start] : active) addInterval(1, 0, q, start, q, e);
        RollbackDSU dsu(n);
        dfs(1, 0, q, dsu, ans);
        return ans;
    }
};
