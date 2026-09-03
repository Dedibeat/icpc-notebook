Bit $i$ belongs to subset $S$ when `(S >> i) & 1`. Add, remove, or toggle it
with `|`, `&`, or `^` using `1 << i`.

### Enumerate all submasks

```
for (int T = S; ; T = (T - 1) & S) {
    use(T);
    if (T == 0) break;
}
```

Across every $S$, this is $O(3^n)$: each bit is outside $S$, in $S\setminus T$,
or in $T$. For nonempty proper submasks, start at `(S - 1) & S` and stop before
zero.

### Held-Karp path DP

$dp[S][v]$ is the minimum cost of a path starting at 0, visiting exactly $S$,
and ending at $v$:

$$
dp[S\cup\{u\}][u]\leftarrow
\min\bigl(dp[S\cup\{u\}][u],\;dp[S][v]+cost[v][u]\bigr).
$$

**Pitfalls:** `1 << n` overflows `int` near $n=31$; use `1LL << n` when needed.
Memory $O(n2^n)$ is often the real limit. Decide path vs. cycle and whether the
start is fixed.
