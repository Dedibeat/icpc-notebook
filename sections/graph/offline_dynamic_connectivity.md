### Usage: append a timeline, then solve

Every API call advances time. `connected(u,v)` does not answer immediately: it
returns an answer index. After the whole timeline is recorded, `solve()` returns
the query answers in those indices.

```cpp
// Input/operations: a 3-vertex timeline; comments show connectivity at that time.
OfflineDynamicConnectivity dc(3);
dc.addEdge(0, 1);
int q0 = dc.connected(0, 1); // true here
int q1 = dc.connected(0, 2); // false here
dc.addEdge(1, 2);
int q2 = dc.connected(0, 2); // true here
dc.removeEdge(0, 1);
int q3 = dc.connected(0, 2); // false here

vector<char> ans = dc.solve();
// Expected output: ans={1,0,1,0} at indices q0,q1,q2,q3 respectively.
```

An edge lifetime is `[add time, remove time)`. Each removal must match one
active insertion, and this implementation does not allow duplicate active
copies of the same undirected edge.
