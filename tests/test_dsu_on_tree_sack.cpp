#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/dsu_on_tree_sack.cpp"

int main() {
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
}
