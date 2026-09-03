### Recurrence and requirement

For one DP layer,

$$
dp_i(j)=\min_{0\le k\le j}
\left(dp_{i-1}(k-1)+C(k,j)\right).
$$

Let $opt_i(j)$ be a minimizing $k$. The optimization is valid only after proving

$$opt_i(j)\le opt_i(j+1).$$

A common sufficient condition is the quadrangle inequality

$$
C(a,c)+C(b,d)\le C(a,d)+C(b,c)
\quad(a\le b\le c\le d),
$$

but this must be checked for the actual cost function.

### Divide-and-conquer step

Compute the midpoint $mid$ while searching only
$[opt_L,\min(mid,opt_R)]$. If its optimum is $best$, recurse on:

- the left half with bounds $[opt_L,best]$;
- the right half with bounds $[best,opt_R]$.

With $O(1)$ cost evaluation, one layer is $O(n\log n)$ and $m$ layers are
$O(mn\log n)$, versus $O(mn^2)$ naively.

### Usage and pitfalls

The printed implementation uses 1-indexed intervals and calls
`comp(1, n, 1, n)` once per layer.

- Define impossible previous states as $+\infty$; only the empty prefix has cost 0.
- Use a wide type for both $C$ and `dp + C`.
- Tie-breaking must preserve a valid monotone optimum.
- Monotonicity is the proof obligation, not a property of the template.
