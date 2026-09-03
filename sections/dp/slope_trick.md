Represent a convex piecewise-linear $f$ by its minimum and two heaps of
breakpoints. The left max-heap contributes $\max(l-x,0)$; the right min-heap
contributes $\max(x-r,0)$.

- Add $\max(a-x,0)$: insert $a$ on the left, rebalancing through the right.
- Add $\max(x-a,0)$: insert $a$ on the right, rebalancing through the left.
- Add $|x-a|$: perform both operations.

The minimum is stored directly. Its minimizer interval is
$[\max(left),\min(right)]$.

### Sliding-window minimum

For $a\le b$,

$$
g(x)=\min_{x-b\le y\le x-a}f(y).
$$

Shift every left breakpoint by $a$ and every right breakpoint by $b$; lazy
offsets avoid touching the heaps.

This structure represents **convex functions only**. Derive the DP transition
as supported convex operations before copying code.
