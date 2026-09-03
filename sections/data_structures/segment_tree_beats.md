### Stored invariant

Each node stores its sum and two extrema in each direction:

- $mx_1$: maximum; $mx_2$: **strict** second maximum; $mx_c$: count of $mx_1$.
- $mn_1$: minimum; $mn_2$: **strict** second minimum; $mn_c$: count of $mn_1$.

### Range `chmin(x)`

- $mx_1\le x$: nothing changes.
- $mx_2<x<mx_1$: only the $mx_c$ maxima change, so update the node in $O(1)$.
- Otherwise descend; more than one value class would change.

Range `chmax` is symmetric. Push lazy addition first, then clamp each child to
the parent's current $mx_1$ and $mn_1$. Pull recomputes strict extrema and
their counts.

Every failed $O(1)$ clamp can be charged to a strict-extremum level change,
giving the usual amortized $O(\log^2 n)$ bound. Never change `<` to `<=` in a
fast-path condition without re-deriving the invariant.
