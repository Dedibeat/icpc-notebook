// Offline add/remove-edge connectivity and component aggregates.
// Record 0-indexed events, then solve with a callback indexed by event time.
// Time O(n + T log(T+1) log(n+1)) plus callbacks, space O(n + T log(T+1)).
struct OfflineDSU {
    using V = long long;
    static V merge(V a, V b) { return a ^ b; } // or min(a, b)
    using E = pair<int, int>;

    int T = 0;
    vector<int> p, sz;
    vector<V> val;
    vector<tuple<int, int, V>> hist;
    vector<tuple<int, int, E>> intervals;
    vector<vector<E>> seg;
    map<E, int> active;

    OfflineDSU(vector<V> a) : p(a.size()), sz(a.size(), 1), val(a) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int u) { return p[u] == u ? u : find(p[u]); }
    V component(int u) { return val[find(u)]; }

    void unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        hist.emplace_back(a, b, val[a]);
        p[b] = a, sz[a] += sz[b], val[a] = merge(val[a], val[b]);
    }
    void rollback(int s) {
        while ((int)hist.size() > s) {
            auto [a, b, old] = hist.back();
            hist.pop_back();
            p[b] = b, sz[a] -= sz[b], val[a] = old;
        }
    }

    int event(char c, int u = 0, int v = 0) {
        E e = minmax(u, v);
        if (c == '+') {
            assert(!active.count(e));
            active[e] = T;
        }
        if (c == '-') {
            assert(active.count(e));
            intervals.emplace_back(active[e], T, e);
            active.erase(e);
        }
        return T++;
    }

    void add(int l, int r, E e) {
        for (l += T, r += T; l < r; l /= 2, r /= 2) {
            if (l & 1) seg[l++].push_back(e);
            if (r & 1) seg[--r].push_back(e);
        }
    }
    template<class F>
    void dfs(int x, F& answer) {
        int s = hist.size();
        for (auto [u, v] : seg[x]) unite(u, v);
        if (x >= T) answer(x - T);
        else dfs(x * 2, answer), dfs(x * 2 + 1, answer);
        rollback(s);
    }
    template<class F>
    void solve(F answer) {
        if (!T) return;
        seg.assign(2 * T, {});
        for (auto [l, r, e] : intervals) add(l, r, e);
        for (auto [e, l] : active) add(l, T, e);
        dfs(1, answer);
    }
};
