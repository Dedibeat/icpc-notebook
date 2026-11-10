### Usage with range add and sum

Copy the default Lazy Segment Tree for this example.

```cpp
vector<vector<int>> g = {{1,2}, {0,3,4}, {0}, {1}, {1}};
HLD<false> h(g); // values on vertices
SegTree st(g.size());
h.process(3, 2, [&](int l, int r) { st.update(l, r, 5); });
long long pathSum = 0;
h.process(3, 2, [&](int l, int r) { pathSum += st.query(l, r); });
auto [l, r] = h.subtree(1);
long long subtreeSum = st.query(l, r);
// pathSum = 20, subtreeSum = 10
```

To load initial vertex values, put `value[v]` at `h.pos[v]` before building
the segment tree. For `HLD<true>`, put each edge's value at its deeper
endpoint. Path and subtree operations then skip the top vertex's incoming
edge. Path intervals may arrive out of order, so use a commutative aggregate
such as sum, min or max.
