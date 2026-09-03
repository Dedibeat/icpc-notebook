All identities are modulo $x^n$ over $\mathbb F_{998244353}$.

### Inverse

Given $a_0\ne0$, start with $b=a_0^{-1}$ and double precision using

$$
b\leftarrow b(2-ab).
$$

If $ab\equiv1\pmod{x^m}$, the new $b$ is correct modulo $x^{2m}$.

### Logarithm and exponential

For $a_0=1$,

$$\log a=\int\frac{a'}a.$$

For $a_0=0$, start with $b=1$ and repeatedly apply

$$b\leftarrow b(1+a-\log b).$$

The implementation uses the notebook NTT and the simple $O(n\log^2 n)$
doubling form. NTT root limits and coefficient normalization still apply.
