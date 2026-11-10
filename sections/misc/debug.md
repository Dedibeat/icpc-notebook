### Before submit

- Samples pass; output format exact.
- Constants copied from the statement: modulus, limits.
- Overflow: products of inputs need `__int128`; INF above every answer.
- Array sizes ($2n$, $n+1$); time and memory estimated.
- Edges: $n=1$, zeros, all equal, $k=n$, empty part.
- Globals reset per test; debug prints and loop caps removed.
- Unproven greedy or formula: stress test first.

### After a WA

- Two WAs: stop. Stress test, or a teammate reads it cold.
- Resubmit only a found bug, never the same code.
- Print the state on the smallest failing test.
- Off-by-one, ties (`<` or `<=`), duplicates, unreachable states.
- `priority_queue` is a max-heap; comparators must be strict.
- Wrong model: rewrite from the invariant, do not patch.

### RE, TLE, MLE

- **RE:** out of bounds, zero division, bad iterators, recursion depth.
- **TLE:** hidden nested work, container copies, slow I/O, hash attacks.
- **MLE:** count $\times$ 8 bytes, recursion stack, not clearing between tests.

### Per member

- **Dedi:** samples first; constants aloud; casework on paper; flush queries.
- **Erdene:** model checked on samples; `__int128` on 64-bit g++; definitions literal.
- **Tamir:** ties in stacks and sorts; verify the full answer; zero parameters.

### Known killers

- Hashing mod $2^{64}$ by overflow: Thue-Morse pairs collide. Use the mod $2^{61}-1$ hash.
- Default `unordered_map/set` can be attacked: use `chash` (Custom Hash).
- $10^6$ nested recursive calls overflow an 8 MB stack: `raise_stack()` or iterate.
- Kuhn is $O(VE)$ and fails on dense adversarial graphs: unit-capacity Dinic.
- Large FFT coefficients lose precision: prefer NTT or FFT-mod.
- `rand()` and `random_shuffle` are banned: use `mt19937`.
