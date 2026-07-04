#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/lazy_segment_tree.cpp"
#include "../sections/graph/heavy_light_decomposition.cpp"

// brute force: values on vertices (or edges to parent), walk the tree
struct Brute {
    int n;
    vector<vector<int>> g;
    vector<int> par, dep;
    vector<long long> val; // val[v]: vertex value, or value of edge (v, par[v])
    Brute(const vector<vector<int>>& g_) : n(g_.size()), g(g_), par(n, -1), dep(n), val(n, 0) {
        vector<int> st = {0};
        vector<bool> vis(n);
        vis[0] = true;
        while (!st.empty()) {
            int v = st.back(); st.pop_back();
            for (int u : g[v]) if (!vis[u]) {
                vis[u] = true;
                par[u] = v;
                dep[u] = dep[v] + 1;
                st.push_back(u);
            }
        }
    }
    vector<int> pathV(int u, int v) { // vertices on u..v path
        vector<int> a, b;
        while (u != v) {
            if (dep[u] >= dep[v]) { a.push_back(u); u = par[u]; }
            else { b.push_back(v); v = par[v]; }
        }
        a.push_back(u);
        a.insert(a.end(), b.rbegin(), b.rend());
        return a;
    }
    vector<int> pathE(int u, int v) { // deeper endpoints of edges on u..v path
        vector<int> res;
        while (u != v) {
            if (dep[u] >= dep[v]) { res.push_back(u); u = par[u]; }
            else { res.push_back(v); v = par[v]; }
        }
        return res;
    }
};

int main() {
    mt19937 rng(2026);
    for (int vals_edges = 0; vals_edges < 2; vals_edges++) {
        for (int it = 0; it < 60; it++) {
            int n = 2 + rng() % 30;
            vector<vector<int>> g(n);
            for (int v = 1; v < n; v++) {
                int p = rng() % v;
                g[p].push_back(v);
                g[v].push_back(p);
            }
            Brute br(g);
            if (!vals_edges) {
                HLD<false> h(g);
                for (int q = 0; q < 100; q++) {
                    int u = rng() % n, v = rng() % n;
                    if (rng() % 2) {
                        long long x = (long long)(rng() % 20) - 10;
                        h.modifyPath(u, v, x);
                        for (int w : br.pathV(u, v)) br.val[w] += x;
                    } else if (rng() % 2) {
                        long long sum = 0;
                        for (int w : br.pathV(u, v)) sum += br.val[w];
                        assert(h.queryPath(u, v) == sum);
                    } else {
                        long long x = (long long)(rng() % 20) - 10;
                        h.modifySubtree(u, x);
                        long long sum = 0;
                        for (int w = 0; w < n; w++) {
                            int a = w;
                            bool in = false;
                            while (a != -1) { if (a == u) { in = true; break; } a = br.par[a]; }
                            if (in) br.val[w] += x;
                        }
                        for (int w = 0; w < n; w++) {
                            int a = w;
                            bool in = false;
                            while (a != -1) { if (a == u) { in = true; break; } a = br.par[a]; }
                            if (in) sum += br.val[w];
                        }
                        assert(h.querySubtree(u) == sum);
                    }
                }
            } else {
                HLD<true> h(g);
                for (int q = 0; q < 100; q++) {
                    int u = rng() % n, v = rng() % n;
                    if (rng() % 2) {
                        long long x = (long long)(rng() % 20) - 10;
                        h.modifyPath(u, v, x);
                        for (int w : br.pathE(u, v)) br.val[w] += x;
                    } else {
                        long long sum = 0;
                        for (int w : br.pathE(u, v)) sum += br.val[w];
                        assert(h.queryPath(u, v) == sum);
                    }
                }
                // subtree of root = all edges; subtree of leaf = empty
                long long all = 0;
                for (int w = 1; w < n; w++) all += br.val[w];
                assert(h.querySubtree(0) == all);
            }
        }
    }
    return 0;
}
