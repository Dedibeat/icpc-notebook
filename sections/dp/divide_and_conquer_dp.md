Divide and Conquer is a dynamic programming optimization.

## Preconditions

Some dynamic programming problems have a recurrence of the form:

$$
dp(i, j) = \min_{0 \le k \le j}
\left\{ dp(i - 1, k - 1) + C(k, j) \right\}
$$

where $ C(k, j) $ is a cost function and  
$ dp(i, j) = 0 $ when $ j < 0 $.

Assume:
$$
0 \le i < m, \quad 0 \le j < n
$$
and evaluating $ C $ takes $ O(1) $ time.

A straightforward evaluation runs in:
$$
O(m n^2)
$$
There are $ m \times n $ states and $ n $ transitions per state.

Let $ opt(i, j) $ be the value of $ k $ that minimizes the recurrence.

If the cost function satisfies the **quadrangle inequality**, then we can prove:

$$
opt(i, j) \le opt(i, j+1)
$$

This is called the **monotonicity condition**.  
For fixed $ i $, the optimal splitting point increases as $ j $ increases.

This allows us to reduce the search range when computing transitions.

If we know $ opt(i, j) $, then for any $ j' < j $:

$$
opt(i, j') \le opt(i, j)
$$

So when computing $ opt(i, j') $, we only need to search a smaller interval.

## Divide and Conquer Optimization

We apply a divide and conquer strategy:

1. Compute $ opt(i, \lfloor n/2 \rfloor) $.
2. Recursively compute:
   - Left half using upper bound $ opt(i, n/2) $
   - Right half using lower bound $ opt(i, n/2) $

By maintaining valid bounds on $ opt $, we reduce the total complexity to:

$$
O(m n \log n)
$$

Each possible value of $ opt(i, j) $ appears in at most $ \log n $ recursion levels.

Importantly, the method does not depend on how balanced the splits are.  
Across each recursion level, every candidate $ k $ is used at most twice.

## Generic Implementation

Below is a common template.  
The function `compute` calculates one row $ i $ of DP values (`dp\_cur`)  
using the previous row (`dp\_before`).  

It must be called as:

$$
`compute(0, n-1, 0, n-1)`
$$

The function `solve` computes all $ m $ rows.



## Things to Watch Out For

The hardest part of Divide and Conquer DP is proving the monotonicity of $ opt $.

A common sufficient condition is the **quadrangle inequality**:

$$
C(a, c) + C(b, d) \le C(a, d) + C(b, c)
\quad \text{for all } a \le b \le c \le d
$$

Many Divide and Conquer DP problems can also be solved using the  
**Convex Hull Trick**, and vice versa.  
Understanding both techniques is highly recommended.
