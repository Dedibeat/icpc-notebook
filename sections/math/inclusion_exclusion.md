For finite sets $A_1,\ldots,A_k$,

$$
\left|\bigcup_i A_i\right|
=\sum_{\emptyset\ne S\subseteq[k]}(-1)^{|S|+1}
 \left|\bigcap_{i\in S}A_i\right|.
$$

To count objects avoiding bad properties $B_i$, apply this to the complement:
total minus single bad sets, plus pair intersections, and so on.

### Standard formulas

Onto functions $[n]\to[k]$:

$$\sum_{i=0}^k(-1)^i\binom ki(k-i)^n.$$

Derangements:

$$!n=n!\sum_{i=0}^n\frac{(-1)^i}{i!}.$$

Inclusion-exclusion is Möbius inversion on the subset lattice. Use subset
transforms when all $2^k$ masks are needed.

**Pitfalls:** define the universe and empty intersection; do not double-count
inside an intersection; use a safe type or modulus.
