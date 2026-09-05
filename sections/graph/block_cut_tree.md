### Recognize it: connectivity after deleting a vertex

A **block** is a maximal biconnected piece; a bridge is a two-vertex block.
`blocks[b]` lists its vertices, and block node `n+b` is joined to each one.
The original vertices stay in the resulting forest, including isolated ones.
An original vertex of degree greater than one in this forest is an articulation
point.

Example: triangle `0-1-2-0`, bridge `2-3`, isolated vertex `4`.
Block labels B and C below are illustrative; build order determines IDs.

```
Original              Block-cut forest
    1                      1
   / \                     |
  0---2---3            0---B---2---C---3
  4                    4
```

Removing `2` separates `0` and `3`; removing `1` does not. Two vertices in a
block remain mutually reachable after deleting any other block vertex, so the
forest path captures exactly the possible separation.

**Example: forbidden-vertex queries.** Given `n m q`, the edges, and queries
`u v x`, print YES iff `u` reaches `v` after deleting `x`; each deletion is
independent. The complete solution is below.

First reject originally disconnected `u,v` with DSU. Otherwise deletion changes
reachability exactly when `x` lies on the block-cut path from `u` to `v`, tested
by `dist(u,x)+dist(x,v)==dist(u,v)`; this includes deleted endpoints. A
temporary LCA root joins components for preprocessing, while deleting a vertex
in another component has no effect.

Dependencies: **BlockCutTree, DSU, LCA**. No self-loops; parallel edges work.
Both DFS routines are recursive, so long chains can overflow the stack.
