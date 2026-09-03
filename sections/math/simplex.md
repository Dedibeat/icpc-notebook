### Canonical input

$$
\max c^Tx\quad\text{subject to }Ax\le b,\;x\ge0.
$$

Phase I adds an artificial variable to find a feasible basis; failure means
infeasible. Phase II uses the real objective; an entering column with no leaving
row means unbounded.

### Modeling conversions

- Equality $a^Tx=b$: add both $a^Tx\le b$ and $-a^Tx\le-b$.
- Free variable: $y=y^+-y^-$ with $y^+,y^-\ge0$.
- Lower bound $y\ge L$: substitute $y=L+z$, $z\ge0$.
- Minimization: maximize the negated objective.

Floating simplex is risky: scale coefficients, avoid nearly dependent
constraints, and verify every returned constraint. Prefer a combinatorial
flow/matching formulation when one exists.
