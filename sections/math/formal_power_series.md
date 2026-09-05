For $A(x)=\sum_i a_i x^i$, `a[i]` is the coefficient of $x^i$; every result
keeps coefficients below $x^n$. All identities are modulo $x^n$ over
$\mathbb F_{998244353}$.

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

### Counting ordered compositions

If allowed part sizes are positive, let $P(x)$ contain one term $x^s$ per
allowed size. Then

$$
1+P+P^2+\cdots=\frac1{1-P}
$$

and the coefficient of $x^n$ counts ordered compositions of $n$. Since
`P(0)=0`, `1-P` has an inverse. For parts 1 and 2, the answer for 5 is 8:

```cpp
// Input: allowed part sizes {1,2}; target sum n=5.
int n=5;
vector<ll> oneMinusP={1,NTT_MOD-1,NTT_MOD-1};
auto ways=fps_inv(oneMinusP,n+1);
// Expected output: ways[5]=8 ordered compositions.
assert(ways[n]==8);
```

The vector is truncated to degree `n`, so read `ways[n]`. Use `fps_log` or
`fps_exp` only when the problem's generating-function identity requires them;
their constant-term restrictions remain in the header.
