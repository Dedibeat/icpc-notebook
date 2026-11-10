### Usage on branching versions

Start with an empty root. Each update copies one path and shares the other
subtrees with older versions. Use the same 0-based inclusive domain for every
operation on a version.

```cpp
Node empty;
Node *a = empty.update(0, 3, 1, 4);
Node *b = a->update(0, 3, 1, -2);
Node *c = a->update(0, 3, 3, 7);
long long sumA = a->query(0, 3, 1, 3); // 4
long long sumB = b->query(0, 3, 1, 3); // 2
long long sumC = c->query(0, 3, 1, 3); // 11
```

Use `n >= 1` and `0 <= p < n`. Choose an associative `merge` with identity
`VID`, the value of untouched leaves. For point assignment, make `apply`
return `x`. Use `__int128` for `V` if sums can exceed `long long`.

Each update allocates nodes with `new`. If memory must be reclaimed between
cases, use a pool with stable addresses and reset it after discarding all
versions of the case. Recursive deletion from each root can double-delete
shared nodes.
