// Dynamic forest: link/cut, connectivity, vertex assignment and path sum.
// Complexity: amortized O(log n) per operation; O(n) memory.
// Usage: LinkCut lct(vector<long long>{2,3}); lct.link(0,1);
// lct.pathQuery(0,1) == 5. Vertices are 0-indexed, initially isolated.
// Pitfalls: cut only DIRECT edges; query only connected vertices.
// All intermediate sums must fit V; use __int128 if necessary.
// High-risk splay code; only commutative aggregates work with this reversal.
struct LinkCut {
    // Customize only this commutative aggregate (and Node's initial values).
    using V = long long;
    static V identity() { return 0; }
    static V merge(V a, V b) { return a + b; }

    struct Node {
        int ch[2] = {-1, -1}, p = -1;
        bool rev = false;
        V val = 0, agg = 0;
    };
    vector<Node> t;

    LinkCut(int n = 0) : t(n) {}
    LinkCut(const vector<V>& a) : t(a.size()) {
        for (int i = 0; i < (int)a.size(); ++i)
            t[i].val = t[i].agg = a[i];
    }
    bool isRoot(int x) const {
        int p = t[x].p;
        return p == -1 || (t[p].ch[0] != x && t[p].ch[1] != x);
    }
    V aggregate(int x) const { return x == -1 ? identity() : t[x].agg; }
    void pull(int x) {
        auto& a = t[x];
        a.agg = merge(merge(aggregate(a.ch[0]), a.val), aggregate(a.ch[1]));
    }
    void applyReverse(int x) {
        if (x != -1) swap(t[x].ch[0], t[x].ch[1]), t[x].rev ^= 1;
    }
    void push(int x) {
        if (!t[x].rev) return;
        for (int c : t[x].ch) applyReverse(c);
        t[x].rev = false;
    }
    void pushPath(int x) {
        vector<int> st{x};
        while (!isRoot(x)) st.push_back(x = t[x].p);
        while (!st.empty()) { push(st.back()); st.pop_back(); }
    }
    void rotate(int x) {
        int p = t[x].p, g = t[p].p, d = t[p].ch[1] == x;
        int b = t[x].ch[d ^ 1];
        if (!isRoot(p)) t[g].ch[t[g].ch[1] == p] = x;
        t[x].p = g; t[p].p = x;
        t[x].ch[d ^ 1] = p; t[p].ch[d] = b;
        if (b != -1) t[b].p = p;
        pull(p); pull(x);
    }
    void splay(int x) {
        pushPath(x);
        while (!isRoot(x)) {
            int p = t[x].p, g = t[p].p;
            if (!isRoot(p))
                rotate((t[p].ch[1] == x) == (t[g].ch[1] == p) ? p : x);
            rotate(x);
        }
    }
    int access(int x) {
        int last = -1;
        for (int y = x; y != -1; y = t[y].p) {
            splay(y); t[y].ch[1] = last; pull(y); last = y;
        }
        splay(x);
        return last;
    }
    void makeRoot(int x) { access(x); applyReverse(x); }
    int findRoot(int x) {
        access(x);
        while (push(x), t[x].ch[0] != -1) x = t[x].ch[0];
        splay(x);
        return x;
    }
    bool connected(int u, int v) { return u == v || findRoot(u) == findRoot(v); }
    bool link(int u, int v) {
        makeRoot(u);
        if (findRoot(v) == u) return false;
        t[u].p = v;
        return true;
    }
    bool cut(int u, int v) {
        makeRoot(u); access(v);
        if (t[v].ch[0] != u || t[u].ch[1] != -1) return false;
        t[v].ch[0] = t[u].p = -1;
        pull(v);
        return true;
    }
    void setValue(int v, V value) { access(v); t[v].val = value; pull(v); }
    V pathQuery(int u, int v) {
        assert(connected(u, v));
        makeRoot(u); access(v);
        return t[v].agg;
    }
};
