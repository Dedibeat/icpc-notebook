### Usage with distinct counts

```cpp
vector<int> a = {0, 1, 0, 2};
vector<pair<int,int>> queries = {{0,3}, {1,4}, {2,2}};
vector<int> freq(3), ans(queries.size());
int distinct = 0;
mo(a.size(), queries,
   [&](int i) { if (++freq[a[i]] == 1) ++distinct; },
   [&](int i) { if (--freq[a[i]] == 0) --distinct; },
   [&](int id) { ans[id] = distinct; }); // {2,3,0}
```

Use half-open query ranges on a static array. This example compresses values
to use them as frequency indices. Start with an empty window on each call.
Store answers by query ID and read them in input order.
