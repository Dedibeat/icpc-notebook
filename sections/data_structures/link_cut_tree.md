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
