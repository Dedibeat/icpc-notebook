### Usage

```cpp
// Input: compressed a[i] in [0,3), queries are half-open [l,r).
vector<int> a = {0, 1, 0, 2};
vector<pair<int,int>> queries = {{0,3}, {1,4}, {2,2}};
// Expected output: ans={2,3,0}; the last query is empty.
auto ans = mo_distinct(a, queries, 3);
```

`freq` counts values in the current window. Adding the first copy increases
`distinct`; removing the last decreases it. Adapt these two updates and the
saved answer for another statistic. Queries are offline; array updates are
unsupported. State resets on every call.
