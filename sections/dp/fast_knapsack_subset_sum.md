### Bitset reachability

The 0/1 transition is `can |= can << weight`, taking
$O(items\cdot SUM/wordsize)$.

### Few distinct positive weights

If positive weights total $S$ and there are $D$ distinct values, then

$$1+2+\cdots+D\le S,\qquad D=O(\sqrt S).$$

Compress equal weights into $(w,k)$. Within each residue modulo $w$, a window of
length $k+1$ processes one weight in $O(S)$, hence $O(S\sqrt S)$ total.

Minimum item count for sum $r+tw$:

$$
new_t=t+\min_{\max(0,t-k)\le j\le t}(old_j-j).
$$

For $k$ copies of an item with weight $w$ and value $v$:

$$
new_t=tv+\max_{\max(0,t-k)\le j\le t}(old_j-jv).
$$

Maintain the min/max with a deque. Bounded max-value knapsack is
$O(types\cdot capacity)$. Zero subset-sum weights do not help; zero-weight
positive-value items contribute every available copy.
