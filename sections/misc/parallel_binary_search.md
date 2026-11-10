### Usage with edge additions

Copy Disjoint Set Union and find the first prefix where each pair is connected.

```cpp
DSU dsu(4);
vector<pair<int,int>> edges = {{0,1}, {1,2}};
vector<pair<int,int>> ask = {{0,0}, {0,1}, {0,2}, {0,3}};
auto ans = parallel_bs(ask.size(), edges.size(),
    [&] { dsu.init(4); },
    [&](int t) { dsu.unite(edges[t].first, edges[t].second); },
    [&](int id) { return dsu.same(ask[id].first, ask[id].second); });
// ans = {0,1,2,3}
```

Prefix `t` contains the first `t` edges, so `0` means connected before any
addition and `edges.size() + 1` means never connected. Edge additions keep
connectivity monotone. Reset the DSU at the start of every replay.
