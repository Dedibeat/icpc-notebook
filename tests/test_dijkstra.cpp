#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/dijkstra.cpp"

int main() {
    vector<vector<pair<int, ll>>> g(5);
    auto add = [&](int u, int v, ll w) { g[u].push_back({v, w}); };
    add(0, 1, 10);
    add(0, 1, 3);
    add(1, 2, 4);
    add(0, 2, 20);
    add(2, 3, 1);
    add(1, 3, 100);
    vector<ll> d = dijkstra(g, 0);
    assert(d[0] == 0);
    assert(d[1] == 3);
    assert(d[2] == 7);
    assert(d[3] == 8);
    assert(d[4] == INFLL);

    vector<vector<pair<int, ll>>> single(1);
    d = dijkstra(single, 0);
    assert(d[0] == 0);
}
