// Articulation points share the Lowlink implementation in bridge.cpp.
// O(n+m) time/memory; handles parallel edges, loops and disconnected graphs.
// Usage: Lowlink g(n); g.addEdge(u,v); g.build(); then inspect g.is_cut[v].
// Pitfalls: insert each undirected edge once; recursive DFS on long chains.
#include "bridge.cpp"
