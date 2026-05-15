#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/heavy_light_decomposition.cpp"

int main() {
    vector<vector<int>> g(5);
    auto add = [&](int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    };
    add(0, 1);
    add(1, 2);
    add(1, 3);
    add(3, 4);

    HLD<false> h(g);
    h.modifyPath(2, 4, 5);
    assert(h.queryPath(2, 4) == 5);
    assert(h.queryPath(0, 0) == 0);
    h.modifySubtree(3, 2);
    assert(h.queryPath(4, 4) == 7);
    assert(h.querySubtree(3) == 7);
}
