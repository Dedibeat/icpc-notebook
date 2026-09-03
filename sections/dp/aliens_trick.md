Let $C(k)$ be the optimum base cost using exactly $k$ components. Add penalty
$\lambda$ per component and ask an oracle for

$$
P(\lambda)=\min_t\bigl(C(t)+\lambda t\bigr).
$$

As $\lambda$ increases, the chosen component count is nonincreasing. For optima
$a$ at $\lambda_1$ and $b$ at $\lambda_2>\lambda_1$, add the two optimality
inequalities to get

$$
(\lambda_2-\lambda_1)(b-a)\le0\quad\Longrightarrow\quad b\le a.
$$

Binary-search where the oracle count crosses $k$. Under the required
discrete-convex/strong-duality condition,

$$
C(k)=\max_\lambda\bigl(P(\lambda)-\lambda k\bigr).
$$

### Oracle checklist

- Return both penalized cost and chosen count.
- Break equal-cost ties consistently to preserve monotonicity.
- Prove penalty bounds whose endpoint counts straddle $k$.
- Monotone count is not enough: justify exact-$k$ dual recovery.

Also called Aliens trick or WQS binary search.
