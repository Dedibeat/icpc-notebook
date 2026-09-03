For $n,a,b\ge0$ and $m>0$,

$$
F(n,m,a,b)=\sum_{0\le i<n}\left\lfloor\frac{ai+b}{m}\right\rfloor.
$$

First remove whole multiples:

- $a=q_am+r_a$ contributes $q_an(n-1)/2$;
- $b=q_bm+r_b$ contributes $q_bn$.

Now $0\le a,b<m$. Let $y=an+b$. If $y<m$, the remainder is zero. Otherwise
reflect the lattice points and swap $a,m$:

$$
n'=\left\lfloor\frac ym\right\rfloor,\qquad b'=y\bmod m,
$$

then continue with $(n',a,m,b')$. This is Euclidean-algorithm-like, hence
logarithmic. For signed inputs, normalize with mathematical floor division;
C++ integer division truncates toward zero.
