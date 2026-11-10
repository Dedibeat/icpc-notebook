#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/dsu_on_tree_sack.cpp"

int main() {
    init_sack(5);
    // small fixed tree, hand-checked
    col[0] = 1; col[1] = 2; col[2] = 1; col[3] = 2; col[4] = 3;
    g[0] = {1, 2};
    g[1] = {0, 3, 4};
    g[2] = {0};
    g[3] = {1};
    g[4] = {1};

    dfs_sz(0, -1);
    dfs(0, -1, true);
    assert(freq[1] == 2);
    assert(freq[2] == 2);
    assert(freq[3] == 1);

    add_subtree(0, -1);
    assert(freq[1] == 0);
    assert(freq[2] == 0);
    assert(freq[3] == 0);

    // randomized: subtree color counts at the answer point vs brute force
    mt19937 rng(66);
    for (int it = 0; it < 100; it++) {
        int n = 1 + rng() % 60;
        init_sack(n);
        assert(timer_sack == 0);
        for (int i = 0; i < MAXN; i += 1 + (i >= 70) * 997) assert(g[i].empty() && freq[i] == 0);
        for (int i = 0; i < n; i++) col[i] = 1 + rng() % 5;
        vector<int> par(n, -1);
        for (int v = 1; v < n; v++) {
            par[v] = rng() % v;
            g[par[v]].push_back(v);
            g[v].push_back(par[v]);
        }
        dfs_sz(0, -1);
        dfs(0, -1, true);
        // verify via st/ft Euler ranges: freq state after full run = subtree(0)
        for (int c = 1; c <= 5; c++) {
            int expect = 0;
            for (int v = 0; v < n; v++) expect += col[v] == c;
            assert(freq[c] == expect);
        }
        // per-vertex check using add_subtree directly (machinery contract)
        add_subtree(0, -1);
        for (int v = 0; v < n; v++) {
            add_subtree(v, +1);
            for (int c = 1; c <= 5; c++) {
                int expect = 0;
                for (int u = 0; u < n; u++) {
                    int a = u;
                    while (a != -1 && a != v) a = par[a];
                    if (a == v) expect += col[u] == c;
                }
                assert(freq[c] == expect);
            }
            add_subtree(v, -1);
        }
    }
    // Documented run: keep=false at the root leaves the state empty, even for
    // a color beyond the tree size, so the next test needs no O(MAXN) reset.
    init_sack(1); col[0] = MAXN-1;
    dfs_sz(0,-1); dfs(0,-1,false);
    assert(freq[MAXN-1] == 0);
    init_sack(1);
    col[0] = 0; dfs_sz(0,-1); dfs(0,-1,true);
    assert(freq[0] == 1);
    add_subtree(0, -1); // clear a retained root before starting another test
    // Many tiny tests exercise cheap resets without a machine-dependent time limit.
    for (int it = 0; it < 100000; it++) {
        init_sack(2); g[0] = {1}; g[1] = {0};
        col[0] = 0; col[1] = MAXN-1;
        dfs_sz(0,-1); dfs(0,-1,false);
        assert(freq[0] == 0 && freq[MAXN-1] == 0);
    }
    init_sack(0);
    assert(timer_sack == 0 && g[0].empty() && g[1].empty());
    return 0;
}
