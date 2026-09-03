Given $y_i=f(i)$ for $0\le i<n$ and $\deg f<n$,

$$
f(x)=\sum_{i=0}^{n-1}y_i
\frac{\prod_{j\ne i}(x-j)}{\prod_{j\ne i}(i-j)}.
$$

At consecutive sample points,

$$
\prod_{j\ne i}(i-j)=i!\,(-1)^{n-1-i}(n-1-i)!.
$$

Prefix/suffix products of $(x-j)$ plus factorials and inverse factorials make
each term $O(1)$, hence $O(n)$ total after one modular inverse.

**Pitfalls:** return $y_x$ immediately when $x$ is a sample index; otherwise
the general numerator contains zero. Modular division normally needs prime
$MOD$ and $n<MOD$. This reconstructs only polynomials of degree below $n$.
