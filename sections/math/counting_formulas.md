### Floor-division blocks

$\lfloor n/i\rfloor$ takes at most $2\sqrt n$ distinct values, so sum over
blocks of equal quotient. The block that starts at $l$ is
$$
q=\lfloor n/l\rfloor,\qquad r=\lfloor n/q\rfloor,\qquad
\lfloor n/i\rfloor=q\ \text{ for all } l\le i\le r.
$$

For two numbers at once (Möbius sums over $\lfloor n/i\rfloor$ and
$\lfloor m/i\rfloor$) take the smaller end,
$r=\min(\lfloor n/\lfloor n/l\rfloor\rfloor,\lfloor m/\lfloor m/l\rfloor\rfloor)$,
for $l\le\min(n,m)$. Typical sums: $\sum_{i\le n}\lfloor n/i\rfloor$ is the
total number of divisors of $1,\dots,n$, and $\sum_{i\le n}i\lfloor n/i\rfloor$
is the total sum of divisors.

```cpp
// sum_{i=1}^{n} i*floor(n/i) = sum of divisors of 1..n (CSES 1082). O(sqrt n).
long long divisor_sum_all(long long n, long long mod) {
    long long ans = 0;
    for (long long l = 1, r; l <= n; l = r + 1) {
        long long q = n / l; r = n / q; // floor(n/i) == q on [l, r]
        __int128 s = (__int128)(l + r) * (r - l + 1) / 2; // sum of i on block
        ans = (ans + (__int128)(q % mod) * (s % mod)) % mod;
    }
    return ans;
}
```

### Exponent reduction

Fermat, for a prime $p$ and $\gcd(a,p)=1$:
$$
a^e\equiv a^{e\bmod(p-1)}\pmod p.
$$

Generalised Euler, for any modulus $m$ and any $a$, valid once
$e\ge\varphi(m)$:
$$
a^e\equiv a^{(e\bmod\varphi(m))+\varphi(m)}\pmod m.
$$

If $e<\varphi(m)$ use $e$ itself. The added $\varphi(m)$ is what keeps the
rule true when $\gcd(a,m)>1$. Power towers ($a_1$ to the power of the tower
$a_2,a_3,\dots$) modulo $m$: compute the exponent tower modulo $\varphi(m)$
recursively, storing every intermediate value as $x$ if $x<m$ and as
$(x\bmod m)+m$ otherwise, including inside fast power. The chain
$m,\varphi(m),\varphi(\varphi(m)),\dots$ reaches $1$ in $O(\log m)$ steps.

```cpp
// a^(b^c) mod prime p with 0^0 = 1 (CSES 1712). Needs modpow (NT essentials).
long long power_tower(long long a, long long b, long long c, long long p) {
    if (a % p == 0) return b == 0 && c > 0 ? 1 : 0; // exponent b^c is 0 or > 0
    return modpow(a, modpow(b, c, p - 1), p);
}
```

### Binomials

**Parity.** $\binom{n}{k}$ is odd exactly when every set bit of $k$ is also
set in $n$, i.e. `(k & n) == k`. XOR pyramid: replacing $a_0,\dots,a_{n-1}$
by $a_i\oplus a_{i+1}$ until one value is left gives the XOR of the $a_i$
with `(i & (n-1)) == i`.

**Vandermonde.** Choose $k$ items from $a$ red and $b$ blue ones:
$$
\sum_i\binom{a}{i}\binom{b}{k-i}=\binom{a+b}{k},\qquad
\sum_i\binom{n}{i}^2=\binom{2n}{n}.
$$

**Hockey stick.** A column of Pascal's triangle sums to the entry below and
to the right; for example $\sum_{i\le n}i=\binom{n+1}{2}$.
$$
\sum_{i=r}^{n}\binom{i}{r}=\binom{n+1}{r+1}.
$$

**Stars and bars** (CSES 1716). Solutions of $x_1+\dots+x_k=n$, the same as
multisets of size $n$ from $k$ kinds:
$$
\binom{n+k-1}{k-1}\ \text{ with } x_i\ge0,\qquad
\binom{n-1}{k-1}\ \text{ with } x_i\ge1\ (n\ge1).
$$

Lower bounds $x_i\ge l_i$: substitute $x_i-l_i$. Upper bound $x_i\le u$ for
all $i$, by inclusion–exclusion over the variables that overflow (stop once
$n-j(u+1)<0$):
$$
\sum_{j\ge0}(-1)^j\binom{k}{j}\binom{n-j(u+1)+k-1}{k-1}.
$$

**Reflection** (CSES 2187). Walks of $L$ steps of $\pm1$ from height $h\ge0$
down to $0$ that never go below $0$. With $u=(L-h)/2$ up-steps:
$$
\binom{L}{u}-\binom{L}{u-1},
$$

and $0$ if $L-h$ is odd or $L<h$. For brackets, $h$ is the balance of the
given prefix and $L$ the number of characters still to place. $h=0$,
$L=2n$ gives Catalan $\frac{1}{n+1}\binom{2n}{n}$.

### Number families

**Stirling numbers of the 2nd kind** $S(n,k)$: ways to split $n$ labeled
items into $k$ nonempty unlabeled groups. Row $n=4$ is $1,7,6,1$.
$$
S(n,k)=kS(n-1,k)+S(n-1,k-1),\qquad
S(n,k)=\frac{1}{k!}\sum_{i=0}^{k}(-1)^i\binom{k}{i}(k-i)^n.
$$

$S(0,0)=1$ and $S(n,0)=0$ for $n>0$. Onto maps from $n$ labeled items to $k$
labeled boxes: $k!\cdot S(n,k)$.

**Bell numbers** $B_n=\sum_kS(n,k)$: all partitions of an $n$-set.
$$
B_{n+1}=\sum_{k=0}^{n}\binom{n}{k}B_k,\qquad
B_0,B_1,\dots=1,1,2,5,15,52,203,877,4140.
$$

**Stirling numbers of the 1st kind** $c(n,k)$ (unsigned): permutations of
$n$ items with exactly $k$ cycles. Row $n=4$ is $6,11,6,1$.
$$
c(n,k)=(n-1)c(n-1,k)+c(n-1,k-1),\qquad
\sum_kc(n,k)x^k=x(x+1)\cdots(x+n-1).
$$

So $\sum_kc(n,k)=n!$, and sorting a permutation with arbitrary swaps takes
exactly $n-(\text{number of cycles})$ swaps.

**Eulerian numbers** $A(n,k)$: permutations of $n$ items with $k$ descents
($p_i>p_{i+1}$). Rows $1,1$ and $1,4,1$ and $1,11,11,1$.
$$
A(n,k)=(k+1)A(n-1,k)+(n-k)A(n-1,k-1),\qquad A(1,0)=1.
$$

Collecting $1,\dots,n$ in left-to-right passes (CSES 2216) takes $d+1$
passes, where $d$ counts the values $x$ such that $x+1$ appears before $x$.
Over all permutations, $A(n,d)$ of them need $d+1$ passes.

**Derangements** $D_n$ (CSES 1717): permutations with no fixed point,
$p_i\ne i$ for every $i$.
$$
D_n=(n-1)(D_{n-1}+D_{n-2})=nD_{n-1}+(-1)^n,\qquad D_0=1,\ D_1=0.
$$

Values $1,0,1,2,9,44,265,1854$. Permutations with exactly $k$ fixed points:
$\binom{n}{k}D_{n-k}$.

### Trees and symmetry

**Cayley.** There are $n^{n-2}$ labeled trees on $n$ vertices ($1$ when
$n=1$). With prescribed degrees $d_1,\dots,d_n\ge1$ summing to $2n-2$:
$$
\frac{(n-2)!}{\prod_i(d_i-1)!}.
$$

Forests on $n$ labeled vertices made of $k$ trees, with $k$ given vertices
in different trees: $kn^{n-k-1}$. Joining $k\ge2$ fixed components of sizes
$s_1,\dots,s_k$ ($n$ vertices in all) into one tree with $k-1$ new edges:
$n^{k-2}s_1s_2\cdots s_k$ ways.

**Prüfer code.** Labeled trees on $n\ge2$ vertices correspond one-to-one to
sequences of length $n-2$ over the $n$ labels. Encode: remove the smallest
leaf and write down its neighbour, $n-2$ times. Vertex $v$ appears
$\deg v-1$ times, so leaves never appear. Decode: set $d_v=\deg v$ from the
counts; for each code value $x$ in order, join $x$ to the smallest $v$ with
$d_v=1$ and decrease $d_v$ and $d_x$ by one; finally join the two vertices
that still have $d_v=1$.

**Burnside.** The number of colourings up to symmetry is the average number
of colourings that a symmetry leaves unchanged (identity included):
$$
\text{orbits}=\frac{1}{|G|}\sum_{g\in G}\mathrm{fix}(g).
$$

Necklaces of $n$ beads in $k$ colours up to rotation (CSES 2209): rotating by
$i$ splits the beads into $\gcd(i,n)$ cycles, each one colour.
$$
N=\frac{1}{n}\sum_{i=0}^{n-1}k^{\gcd(i,n)}
=\frac{1}{n}\sum_{d\mid n}\varphi(d)k^{n/d}.
$$

Bracelets (rotations and reflections) number $(N+R)/2$, where $R$ is the
average count fixed by a reflection: $R=k^{(n+1)/2}$ for odd $n$ and
$R=\frac{1}{2}(k^{n/2}+k^{n/2+1})$ for even $n$. An $n\times n$ grid up to
rotation (CSES 2210), from the identity, the half turn and the two quarter
turns:
$$
\frac{1}{4}\left(k^{n^2}+k^{\lceil n^2/2\rceil}+2k^{\lceil n^2/4\rceil}\right).
$$

### Lattice and distance

**Manhattan to Chebyshev.** Rotate by $45^\circ$ with $u=x+y$, $v=x-y$:
$$
|\Delta x|+|\Delta y|=\max(|\Delta u|,|\Delta v|),\qquad
\max(|\Delta x|,|\Delta y|)=\frac{|\Delta u|+|\Delta v|}{2}.
$$

The farthest Manhattan pair is the larger of $\max u-\min u$ and
$\max v-\min v$. The points within Manhattan distance $d$ of a point form an
axis-parallel square in $(u,v)$, so 2D prefix sums and sweeps apply.

**Pick.** For a simple polygon with integer vertices, area $A$, $I$ lattice
points strictly inside and $B$ on the boundary:
$$
2A=2I+B-2,\qquad B=\sum_{\text{edges}}\gcd(|\Delta x|,|\Delta y|).
$$

Get $2A$ from the shoelace formula, so $I=(2A-B+2)/2$ stays in integers.

**Pitfalls:** reduce the exponent modulo $p-1$, never modulo $p$; keep
$\varphi(m)$ added back when $\gcd(a,m)>1$; Burnside averages over the whole
group, identity included; $S(n,0)=0$ for $n>0$ but $S(0,0)=1$; $n^{n-2}$
needs the $n=1$ special case.
