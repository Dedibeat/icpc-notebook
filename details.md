# Notebook follow-ups

## Virtual Tree

Add a usage block that builds LCA, calls `vtree` with the marked vertices, and
computes their total pairwise distance. Give each virtual edge the original
tree distance between its endpoints. Process children before parents and add
`length * count * (k - count)` for each edge, where `count` is the number of
marked vertices below it and `k` is the total number of distinct marks. Use
`__int128` if the sum can exceed `long long`. With binary-lifting LCA, each
query takes `O(k log k + k log n)` after preprocessing. Test duplicate marks,
an empty set, a marked ancestor and a branching LCA that was never marked.

## Centroid Decomposition

Show how to mark vertices and query the distance to the nearest marked vertex.
Walk the centroid parent chain in both operations. At each centroid `c`,
store the minimum distance from `c` to a marked vertex. The query minimizes
that value plus the distance from the query vertex to `c`. With binary-lifting
LCA distances, each operation takes `O(log^2 n)`. Build the distance oracle
per component if supporting forests. Test the empty marked set, repeated
marks, a query at a marked vertex and disconnected components.

## Rerooting DP

Add a weighted-distance example that computes the sum of distances from every
vertex. Show how `merge` combines counts and sums, `addRoot` counts the current
vertex and `addEdge` adds `weight * count` when crossing an edge. Use
constant-time edge-weight lookup to keep the traversal linear. Test a
singleton, zero-weight edges and a small weighted tree with unequal answers.
