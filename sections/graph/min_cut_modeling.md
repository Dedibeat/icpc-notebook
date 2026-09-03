Choose $INF$ strictly larger than every feasible finite cut, often
$1+\sum_v|cost_v|$. After max flow, residual-reachable vertices form the
source side of a minimum cut.

### Maximum-weight closure

- $profit_v>0$: edge $s\to v$ with capacity $profit_v$.
- $profit_v<0$: edge $v\to t$ with capacity $-profit_v$.
- Choosing $u$ requires $v$: edge $u\to v$ with capacity $INF$.
- Answer: $\sum_v\max(0,profit_v)-\text{mincut}$.

### Bipartite minimum-weight vertex cover

- $s\to u$ for each left vertex; capacity is its weight.
- $v\to t$ for each right vertex; capacity is its weight.
- For every graph edge, add $u\to v$ with capacity $INF$.
- Cover = left vertices outside the source side + right vertices inside it.

### Binary labeling

Use $s\to v$ for the cost of label 1, $v\to t$ for label 0, and undirected
capacity $w$ for disagreement penalty $w$.

**Pitfalls:** an $INF$ edge is hard only if no optimum can cut it. Decide which
side means "chosen." General pairwise rewards require submodularity and may not
be graph-representable.
