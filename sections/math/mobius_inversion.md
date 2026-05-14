## Möbius Function

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
## Inversion Formula

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

## Common CP Applications

Counting pairs with $\gcd(i,j)=1$:
$$
\sum_{d=1}^{n}
\mu(d)
\left\lfloor \frac{n}{d} \right\rfloor^2
$$

Used to:

- Remove overcounting over divisors
- Transform sums over $\gcd$
- Invert divisor summations

## Linear Sieve for $\mu$ (O(n))
