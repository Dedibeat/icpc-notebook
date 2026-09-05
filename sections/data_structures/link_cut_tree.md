### Mental model

The represented forest is split into preferred paths, each stored as a splay
tree. A splay parent may also be a virtual/path parent when the node is not its
actual splay child.

### Operations

- `access(v)`: expose the represented-tree path from its root to `v`.
- `makeRoot(v)`: `access(v)`, then lazily reverse the exposed path.
- `link(u,v)`: make `u` a represented-tree root, then attach it under `v`.
- `cut(u,v)`: `makeRoot(u)`, `access(v)`, then verify and remove the direct edge.
- `pathQuery(u,v)`: `makeRoot(u)`, `access(v)`; `v` stores the path aggregate.

Before each rotation, push reversals from ancestors; after changing children,
pull aggregates. This version uses commutative path sum. Noncommutative
aggregates need forward and reverse values; path updates need another lazy tag.

### Usage: link, query, update, and cut

Vertices start isolated. Paths include both endpoint vertices. `link` and `cut`
return whether the requested forest change was valid.

```cpp
// Input: three isolated vertices with values {2,3,5}.
LinkCut lct(vector<long long>{2, 3, 5});
bool a = lct.link(0, 1);
bool b = lct.link(1, 2);
bool cycle = lct.link(0, 2);
long long sum1 = lct.pathQuery(0, 2);

// Effect: set vertex 1 to 7, then remove direct edge (1,2).
lct.setValue(1, 7);
long long sum2 = lct.pathQuery(0, 2);
bool removed = lct.cut(1, 2);
bool joined = lct.connected(0, 2);
// Expected: a,b,removed=true; cycle,joined=false; sum1=10; sum2=14.
```

Never call `pathQuery(u,v)` while disconnected; it asserts connectivity.
