### Use: add to an interval, then ask its sum

Ranges are half-open `[l,r)`. `init(a)` builds the initial values and `init(n)` fills
leaves with `VID` (zero for the default). Empty ranges return `VID`.

```cpp
// Input: a={2,1,4}; half-open update/query intervals.
SegTree st;
st.init(vector<long long>{2, 1, 4});
// Add 3 to a[0..2), producing {5,4,4}.
st.update(0, 2, 3);
// Expected sum over a[1..3) is 8.
auto sum = st.query(1, 3);
```

### Adapt: range add, range minimum

Replace the marked block with the following. Build from a vector of actual
values: `VID` is a query identity, not an initial array value.

```cpp
using V = long long;
using L = long long;
static constexpr V VID = LLONG_MAX;
static constexpr L LID = 0;
static V merge(V a, V b) { return min(a, b); }
static V applyVal(V a, L f, int) { return a + f; }
static L compose(L a, L f) { return a + f; }
```

On the same array and update above, `query(1,3)` returns **4**.
Real values and all updated values must fit `long long`.

### Adapt: range assignment, range sum

Replace the marked block with the following. The sentinel `LLONG_MIN` is
reserved: it cannot be an assigned value. Assigning zero works.

```cpp
using V = long long;
using L = long long;
static constexpr V VID = 0;
static constexpr L LID = LLONG_MIN;
static V merge(V a, V b) { return a + b; }
static V applyVal(V a, L f, int len) {
    return f == LID ? a : f * len;
}
static L compose(L a, L f) { return f == LID ? a : f; }
```

Starting from `[2,1,4]`, `update(0,2,0)` assigns zero to two cells and `query(0,3)` returns **4**.
All three configurations build in $O(n)$, use $O(n)$ memory, and take
$O(\log n)$ per operation. For other configurations, `merge` must be
associative with identity `VID`; applying a tag must agree with merging
the updated children. `compose(old,new)` must preserve that order.
