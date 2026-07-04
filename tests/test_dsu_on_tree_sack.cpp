#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/dsu_on_tree_sack.cpp"

int main() {
    // small fixed tree, hand-checked
    for (int i = 0; i < 5; i++) g[i].clear(), cnt[i] = 0;
    timer_sack = 0;
    col[0] = 1; col[1] = 2; col[2] = 1; col[3] = 2; col[4] = 3;
    g[0] = {1, 2};
    g[1] = {0, 3, 4};
    g[2] = {0};
    g[3] = {1};
    g[4] = {1};

    dfs_sz(0, -1);
    dfs(0, -1, true);
    assert(cnt[1] == 2);
    assert(cnt[2] == 2);
    assert(cnt[3] == 1);

    add_subtree(0, -1);
    assert(cnt[1] == 0);
    assert(cnt[2] == 0);
    assert(cnt[3] == 0);

    // randomized: subtree color counts at the answer point vs brute force
    mt19937 rng(66);
    for (int it = 0; it < 100; it++) {
        int n = 1 + rng() % 60;
        for (int i = 0; i < n; i++) {
            g[i].clear();
            col[i] = 1 + rng() % 5;
            cnt[col[i]] = 0;
        }
        timer_sack = 0;
        vector<int> par(n, -1);
        for (int v = 1; v < n; v++) {
            par[v] = rng() % v;
            g[par[v]].push_back(v);
            g[v].push_back(par[v]);
        }
        dfs_sz(0, -1);
        dfs(0, -1, true);
        // verify via st/ft Euler ranges: cnt state after full run = subtree(0)
        for (int c = 1; c <= 5; c++) {
            int expect = 0;
            for (int v = 0; v < n; v++) expect += col[v] == c;
            assert(cnt[c] == expect);
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
                assert(cnt[c] == expect);
            }
            add_subtree(v, -1);
        }
    }
    return 0;
}
