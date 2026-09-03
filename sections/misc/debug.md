### Before submit

- Re-read constraints and output format; submit the right file.
- Test smallest, degenerate, duplicate, and maximum cases.
- Check overflow, memory, recursion depth, and per-test reset.
- Estimate time from the actual worst-case operation count.

### Wrong answer

- Print the computed state, not only the final answer.
- Hand-simulate a tiny counterexample and add assertions.
- Check off-by-one bounds, $N/M$ mixups, ties, duplicates, and unreachable states.
- Verify STL/API semantics and strict comparator ordering.
- Explain the proof and code to a teammate; let fresh eyes inspect it.
- If the model is wrong, rewrite from the invariant instead of patching symptoms.

### Runtime, time, and memory

- **RE:** out-of-bounds, uninitialized data, zero division, invalid iterators,
  failed assertions, or recursion depth.
- **TLE:** hidden nested work, infinite loops, copying large containers, slow I/O,
  or an adversarial hash/table case.
- **MLE:** actual peak allocation, recursion stack, retained globals, or failure to
  clear between tests.

### Known killers

- Hashing modulo $2^{64}$ by overflow: Thue-Morse pairs collide for every base.
  Use the notebook's modulo-$2^{61}-1$ hash.
- Default `unordered_map/set`: adversarial keys may share one GCC bucket. Use
  `chash` from `misc/custom_hash.cpp`.
- A chain of $10^6$ recursive calls overflows an 8 MB stack. Use
  `raise_stack()` or an iterative traversal.
- Kuhn matching is $O(VE)$ and fails on dense adversarial graphs. Use
  unit-capacity Dinic when needed.
- Large FFT coefficient energy loses precision. Prefer NTT or FFT-mod.
- A non-strict comparator such as `<=` causes undefined behavior.
- `rand()` and `random_shuffle` are banned here; use `mt19937`.
