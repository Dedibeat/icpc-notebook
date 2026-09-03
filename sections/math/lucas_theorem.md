### Lucas

For prime $p$, write $n$ and $k$ in base $p$ with digits $n_i,k_i$:

$$
\binom nk\equiv\prod_i\binom{n_i}{k_i}\pmod p.
$$

If any $k_i>n_i$, the result is zero.

### Kummer

The exponent of prime $p$ in $\binom nk$ equals the number of carries when
adding $k$ and $n-k$ in base $p$. Use this for divisibility or $p$-adic
valuation.

The code precomputes through $p-1$, so it needs $O(p)$ memory. For large $p$
and few queries, compute each digit-level binomial multiplicatively.
