### Möbius function

The Möbius function $\mu(n)$ is defined as
$$
\mu(n)=
\begin{cases}
1 & \text{if } n=1, \\
(-1)^k & \text{if } n \text{ is a product of } k \text{ distinct primes}, \\
0 & \text{if } n \text{ has a squared prime factor}.
\end{cases}
$$

Key identity:
$$
\sum_{d \mid n} \mu(d) =
\begin{cases}
1 & \text{if } n=1, \\
0 & \text{if } n>1.
\end{cases}
$$
### Inversion formula

If
$$
F(n) = \sum_{d \mid n} f(d),
$$
then
$$
f(n) = \sum_{d \mid n} \mu(d)\,F\!\left(\frac{n}{d}\right).
$$

Equivalently, in Dirichlet convolution form:
$$
F = f * 1
\quad \Longleftrightarrow \quad
f = F * \mu.
$$

### Common application

The number of ordered pairs $1\le i,j\le n$ with $\gcd(i,j)=1$ is
$$
\sum_{d=1}^{n}
\mu(d)
\left\lfloor \frac{n}{d} \right\rfloor^2
$$

Use Möbius inversion to:

- remove overcounting over divisors;
- transform sums constrained by $\gcd$;
- invert divisor summations.

### Implementation

`mobius_sieve(n)` fills `mu[1..n]` in $O(n)$.
