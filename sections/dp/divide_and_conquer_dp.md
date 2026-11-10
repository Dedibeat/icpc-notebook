### Recurrence and requirement

For one DP layer,

$$
dp_i(j)=\min_{i-1\le k<j}
\left(dp_{i-1}(k)+C(k,j)\right),\qquad i\ge 2.
$$

$dp_i(j)$ is the cost of partitioning $[0,j)$ into exactly $i$ nonempty
groups. $C(k,j)$ costs $[k,j)$ and $dp_1(j)=C(0,j)$ for $j\ge 1$.
Let $opt_i(j)$ be the smallest minimizing $k$. Prove

$$opt_i(j)\le opt_i(j+1).$$

A common sufficient condition is the quadrangle inequality

$$
C(a,c)+C(b,d)\le C(a,d)+C(b,c)
\quad(a\le b\le c\le d),
$$

but this must be checked for the actual cost function.

### Divide-and-conquer step

Compute the midpoint $mid$ while searching only
$[opt_L,\min(mid-1,opt_R)]$. If its optimum is $best$, recurse on the two halves.

- the left half with bounds $[opt_L,best]$;
- the right half with bounds $[best,opt_R]$.

With $O(1)$ cost evaluation, one layer is $O(n\log n)$ and $m$ layers are
$O(mn\log n)$, versus $O(mn^2)$ naively.

### Usage and pitfalls

Call `divide_and_conquer_dp(n, groups, cost)` with a half-open cost function.
For layer `g` the code fills endpoints from `g` to `n` and starts the
split search at `g-1`. This keeps impossible prefixes out of the search.

- Use a wide type for both $C$ and `dp + C`.
- Tie-breaking must preserve a valid monotone optimum.
