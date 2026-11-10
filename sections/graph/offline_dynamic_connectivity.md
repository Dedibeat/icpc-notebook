### Usage on an edge timeline

`event(c,u,v)` appends an event and returns its 0-based time. Use `+` and
`-` for undirected edges and `?` for a query slot. After recording the timeline,
`solve(answer)` calls `answer(t)` at every event with the DSU in that event's
state. Size `ask` and `ans` for all events and initialize `ask` to `-1`.

```cpp
OfflineDSU dsu(values);
dsu.event('+', u, v);           // link
dsu.event('-', u, v);           // cut
int t = dsu.event('?');         // query time
ask[t] = u;

dsu.solve([&](int t) {
    if (ask[t] != -1)
        ans[t] = dsu.component(ask[t]); // component XOR
    // dsu.find(u)                   // component root
    // dsu.find(u) == dsu.find(v)    // connected?
});
// Print answers in time order where ask[t] != -1.
```

Edge lifetimes are half-open. An edge is present at its addition and absent
at its removal. Each removal must match an active insertion, and each edge
has at most one active copy. Edges still active at the end last until `T`.

Callback order can differ from time order when `T` is not a power of two.
Keep the callback read-only with respect to the DSU. Use an associative,
commutative `merge` for fixed vertex values. Keep union by size and omit path
compression so rollback only has to undo successful unions.
