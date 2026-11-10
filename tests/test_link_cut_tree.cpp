#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/link_cut_tree.cpp"

vector<int> path(const vector<set<int>>& g, int s, int t) {
    vector<int> p(g.size(), -1), result;
    queue<int> q; q.push(s); p[s] = s;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : g[v]) if (p[u] < 0) p[u] = v, q.push(u);
    }
    if (p[t] < 0) return {};
    for (int v = t;; v = p[v]) {
        result.push_back(v);
        if (v == s) break;
    }
    return result;
}
int main() {
    LinkCut empty;
    assert(empty.t.empty());
    LinkCut example(vector<long long>{2, 3, 5});
    assert(example.link(0, 1) && example.link(1, 2));
    assert(!example.link(0, 2) && !example.cut(0, 2));
    assert(example.pathQuery(0, 2) == 10);
    example.setValue(1, 7);
    assert(example.pathQuery(2, 0) == 14);
    assert(example.cut(2, 1) && !example.cut(1, 2));
    assert(!example.connected(0, 2));
    mt19937 rng(45);
    for (int n = 1; n <= 30; ++n) {
        vector<long long> value(n);
        for (auto& x : value) x = (int)(rng() % 21) - 10;
        LinkCut lct(value);
        vector<set<int>> g(n);
        for (int it = 0; it < 10000; ++it) {
            int u = rng() % n, v = rng() % n, type = rng() % 6;
            auto p = path(g, u, v);
            if (type == 0) {
                bool valid = p.empty();
                assert(lct.link(u, v) == valid);
                if (valid) g[u].insert(v), g[v].insert(u);
            } else if (type == 1) {
                bool valid = g[u].count(v);
                assert(lct.cut(u, v) == valid);
                if (valid) g[u].erase(v), g[v].erase(u);
            } else if (type == 2) {
                value[u] = ((long long)(rng() % 2001) - 1000) * 1000000000LL;
                lct.setValue(u, value[u]);
            } else if (type == 3) {
                lct.makeRoot(u);
                assert(lct.findRoot(u) == u);
            } else {
                assert(lct.connected(u, v) == !p.empty());
                if (!p.empty()) {
                    long long want = 0;
                    for (int x : p) want += value[x];
                    assert(lct.pathQuery(u, v) == want);
                }
            }
        }
    }
    const int n = 200000;
    LinkCut chain(n);
    for (int i = 1; i < n; ++i) assert(chain.link(i - 1, i));
    assert(chain.pathQuery(0, n - 1) == 0);
    chain.setValue(n / 2, 1000000000000LL);
    for (int it = 0; it < 10; ++it) {
        chain.makeRoot(it % 2 ? 0 : n - 1);
        assert(chain.pathQuery(n - 1, 0) == 1000000000000LL);
    }
    assert(!chain.cut(0, n - 1));
    assert(chain.cut(n / 2 - 1, n / 2));
    assert(!chain.connected(0, n - 1));
    chain = LinkCut(1);
    assert(chain.pathQuery(0, 0) == 0);
    assert(!chain.link(0, 0) && !chain.cut(0, 0));
}
