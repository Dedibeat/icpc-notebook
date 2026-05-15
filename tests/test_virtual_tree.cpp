#include <bits/stdc++.h>
using namespace std;

#define main virtual_tree_original_main
#include "../sections/graph/virtual_tree.cpp"
#undef main

int main() {
    n = 7;
    timer = 0;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        vadj[i].clear();
        at_a[i].clear();
        a[i] = 0;
    }

    auto add_edge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(1, 3);
    add_edge(1, 4);
    add_edge(2, 5);
    add_edge(2, 6);

    dfs(0, 0);

    vector<int> nodes = vtree({5, 3, 4});
    vector<int> expected = {0, 1, 3, 4, 5};
    sort(expected.begin(), expected.end(), sort_tin);
    assert(nodes == expected);

    set<pair<int, int>> edges;
    for (int u : nodes) {
        for (int v : vadj[u]) edges.insert({u, v});
    }
    assert(edges.count({0, 1}));
    assert(edges.count({0, 5}));
    assert(edges.count({1, 3}));
    assert(edges.count({1, 4}));
    assert(edges.size() == 4);

    nodes = vtree({4, 3});
    expected = {1, 3, 4};
    sort(expected.begin(), expected.end(), sort_tin);
    assert(nodes == expected);
    edges.clear();
    for (int u : nodes) {
        for (int v : vadj[u]) edges.insert({u, v});
    }
    assert(edges.count({1, 3}));
    assert(edges.count({1, 4}));
    assert(edges.size() == 2);
}
