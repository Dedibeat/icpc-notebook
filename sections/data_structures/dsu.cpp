// Disjoint Set Union.
// Complexity: amortized O(alpha(n)).
// Pitfalls: init per test case; unite returns false if already same set.
// Usage: DSU d(n); d.unite(u, v); d.same(u, v); d.size(u);
struct DSU {
    vector<int> p, sz;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sz.assign(n, 1);
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
    bool same(int a, int b) {
        return find(a) == find(b);
    }
    int size(int x) {
        return sz[find(x)];
    }
};
