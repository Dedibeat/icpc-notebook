# ICPC Notebook Source Evaluation

This is a skeptical review of the current `sections/` snippets. It does not
assume the code is correct. No snippet should be printed as trusted notebook
material until it has the listed tests or an equivalent stress test.

| Algorithm | Include / Maybe / Skip | Reason | Main risks | Needed tests | Suggested final location |
|---|---:|---|---|---|---|
| Short segment tree | Include | Short, standard, useful | Fixed `N`, operation is sum-only | Empty-ish ranges, point updates, large sums | `data_structures/segment_tree_iterative.cpp` |
| Bridge finding | Include | Standard and compact | Multiedges, recursion depth | Multiedge, disconnected, line, tree, cycle | `graph/bridges.cpp` |
| Articulation points | Include | Standard and useful | Duplicate reporting, recursion depth | Root cases, disconnected, cycle, line | `graph/articulation_points.cpp` |
| KMP prefix | Include | Very short, reliable | Only prefix array, no search wrapper | Empty, repeated chars, full match | `string/kmp_prefix.cpp` |
| Z-function | Include | Short and standard | `[l,r)` convention confusion | Empty, all same, no repeats | `string/z_function.cpp` |
| Rolling hash | Maybe | Useful, tiny | Collisions, no double hash | Equal substrings, collision sanity, bounds | `string/rolling_hash.cpp` |
| Manacher odd | Maybe | Correct-looking but only odd palindromes | Return convention unclear | Odd/even examples, length 0/1 | `string/manacher.cpp` |
| Minimum rotation | Maybe | Useful and short | Tie behavior, empty string | All equal, periodic, length 1 | `string/min_rotation.cpp` |
| Aho-Corasick | Maybe | Good contest value | Lowercase-only, no positions, post-build mutation | Duplicate patterns, suffix patterns, invalid chars | `string/aho_corasick.cpp` |
| Suffix array cyclic shifts | Maybe | Standard base code | Cyclic-only unless sentinel added | `banana`, all same, high-byte chars, empty | `string/suffix_array.cpp` |
| Convex hull | Maybe | Useful but floating implementation | Precision, all collinear, orientation sign/order | Duplicates, collinear, 1/2 points | `geometry/convex_hull.cpp` |
| Dinic | Maybe | Important algorithm | Capacity scaling assumptions, recursive DFS depth | Zero cap, disconnected, bipartite, large cap | `graph/dinic.cpp` |
| CRT | Maybe | Useful and compact | Requires `egcd`, lcm overflow | Non-coprime valid/invalid, negatives, overflow | `math/crt.cpp` |
| Number theory essentials | Maybe | Useful helpers | `inv` assumes prime mod | Negative egcd, composite inverse, modpow overflow | `math/number_theory_basics.cpp` |
| Sieve | Maybe | Useful | Macro dependencies, `lim <= MAX_PR`, bitset size | `lim` 0/1/2, exact max, prime count | `math/sieve.cpp` |
| Gaussian elimination mod | Maybe | Useful but incomplete output | Only rank returned, prime mod only | No solution, many solutions, negative coeffs | `math/gauss_mod.cpp` |
| XOR basis max | Maybe | Useful but should be snippet, not full program | Signed int bit 31, reset per test | Zero, duplicates, high bit, multi-test | `math/xor_basis.cpp` |
| Subset XOR count | Maybe | Same basis, but name is misleading | Counts distinct XOR values, overflow `2^rank` | Rank 0/1/31/63, duplicates | `math/xor_basis.cpp` |
| Mobius sieve | Maybe | Useful | Global arrays, caller must respect `n <= N` | `n=1`, prime, square, max n, repeated calls | `math/mobius.cpp` |
| D&C DP opt | Maybe | Valuable pattern | Preconditions must be proven, complexity docs need clarity | Compare to brute DP, monotone/nonmonotone costs | `dp/divide_conquer_dp.cpp` |
| Line container CHT | Maybe | Valid under printed notebook `#define int long long` assumption | Global min/max flag, empty query, equal slopes need stress | Random vs brute lines/queries, equal slopes | `data_structures/cht_line_container.cpp` |
| Lazy segment tree | Include | Assignment lazy tree is now concrete and handles assigning 0 | Sum/assignment only; adapt carefully for other ops | Assign 0, overlap updates, random vs brute | `data_structures/lazy_segment_tree.cpp` |
| Treap implicit | Maybe | Useful, moderate length | No node constructor/allocation, null `t2` in reverse | Insert/build, reverse empty/single/full | `data_structures/implicit_treap.cpp` |
| Priority queue with delete | Maybe | Tiny trick | Deleting absent values, `top()` on empty | Duplicates, delete-before-top, empty | `data_structures/heap_delete.cpp` |
| DSU on segtree | Maybe | Specialized but useful | Global `maxn`, pool size, reset per test | Merge empty, duplicate points, many nodes | `data_structures/mergeable_segtree.cpp` |
| PBDS / rope notes | Maybe | Useful reference | `.cpp` is not one compilable file, `less_equal` PBDS unsafe | Ordered multiset duplicate erase | `misc/gnu_extensions.md` |
| Random mt19937 | Include | Useful small snippet | Modulo bias if used seriously | Deterministic seed variant | `misc/random.cpp` |
| Random hashing | Maybe | Useful trick | Depends on `rng`, collision probability | Add/remove/toggle invariants | `misc/random_hashing.cpp` |
| `nth_element` | Include | One-line useful note | `k` bounds | `k=0`, `k=n-1`, duplicates | `misc/nth_element.cpp` |
| Simulated annealing | Skip | Pseudocode and risky for printed notebook | Not typeable as-is, problem-specific | Problem-specific only | `misc/simulated_annealing.md` |
| FFT double | Maybe | Proven style but macro-heavy | KACTL macros, precision, non-power sizing | Random convolution vs naive, large coefficients | `math/fft.cpp` |
| FFT mod | Maybe | Dependency on local FFT snippet is now explicit and test-covered | Floating precision limits, inputs must be in `[0, mod)` | Random mod convolution | `math/fft_mod.cpp` |
| FWHT | Include | Replaced pseudocode with compact C++17 XOR transform | Size must be power of two; modular inverse needed for modular types | XOR convolution vs naive | `math/fwht.cpp` |
| Zeta/Mobius transforms | Skip until fixed | File missing closing braces; external `PrimeEnumerate` | Does not compile | Subset/divisor transforms vs brute | `math/zeta_mobius_transform.cpp` |
| Fraction finder | Maybe | Niche but tested per comment | Hard to explain quickly, template dependency | Monotone predicates, exact boundaries | `math/fraction_binary_search.cpp` |
| Catalan note | Maybe | Tiny formula only | Needs modular computation note | `n=0/1/small` | `math/combinatorics.md` |
| Global min cut | Maybe | Valuable but macro-heavy KACTL style | Dense matrix only, int overflow | Small graphs vs brute cuts | `graph/global_min_cut.cpp` |
| Max clique | Maybe | Useful for rare problems, stress-tested comment | GPL license, `bitset<200>`, long code | Random vs brute `n <= 20` | `graph/max_clique.cpp` |
| HLD | Maybe | Now prints with a small range-add/range-max `Node` dependency | Recursive DFS depth; default operation is only add/max | Paths/subtrees vs brute | `graph/hld.cpp` |
| Virtual tree | Maybe | Generic builder is compact after local LCA-order fix, but file still includes problem-specific DP | Full file is not notebook-shaped; globals and recursive DFS depth | Empty/one key, root included, ancestor/descendant, repeated builds | `graph/virtual_tree.cpp` |
| DSU on tree sack | Maybe | Completed common globals, Euler preprocessing, and cleanup logic | User must add problem-specific query answers | Subtree color counts vs brute | `graph/dsu_on_tree.cpp` |
| Kruskal reconstruction tree | Maybe | Completed DSU, edge sorting, weights, and build routine | Assumes connected graph for single root | MST/query examples | `graph/kruskal_reconstruction_tree.cpp` |
| Critical cities dominator | Skip | Too long/specialized for ICPC notebook | Complex, reachability UB, hard to explain | Directed dominator brute small graphs | `graph/dominator_tree.cpp` |
| LCP array | Include | Replaced macro/RMQ fragment with trusted Kasai helper | Requires valid suffix array input | Suffix LCP vs brute | `string/lcp.cpp` |

Highest-confidence keepers after adding tests: iterative segment tree, bridges,
articulation points, KMP, Z-function, random notes, and `nth_element`.

## Small Safe-Fix Pass - 2026-05-15

Applied only minimal, high-confidence fixes with targeted regression tests.

| Issue | Change | Regression test | Result |
|---|---|---|---|
| Iterative segment tree sum overflow | Changed tree storage, update value, and query result from `int` to `long long`. | `tests/test_short_segment_tree.cpp` checks large sums, empty range, point update to negative. | Passed: `g++ -std=c++17 -Wall -Wextra -pedantic tests/test_short_segment_tree.cpp -o /tmp/test_short_segment_tree && /tmp/test_short_segment_tree` |
| Rolling hash signed `char` ambiguity | Hashes `(unsigned char)s[i] + 1` instead of raw `char`. | `tests/test_rolling_hash.cpp` checks repeated substrings and high-byte characters. | Passed: `g++ -std=c++17 -Wall -Wextra -pedantic tests/test_rolling_hash.cpp -o /tmp/test_rolling_hash && /tmp/test_rolling_hash` |
| Mobius sieve array bound and stale globals | Resized arrays to `N + 1` and reset sieve state inside `mobius_sieve(n)`. | `tests/test_mobius_inversion.cpp` checks known values through 20 and repeated call through 10. | Passed: `g++ -std=c++17 -Wall -Wextra -pedantic tests/test_mobius_inversion.cpp -o /tmp/test_mobius_inversion && /tmp/test_mobius_inversion` |
| Lazy-delete heap missing `PQ` alias | Replaced `PQ<int>` with `priority_queue<int>` and guarded cleanup loop against empty insert heap. | `tests/test_priority_queue_with_delete.cpp` checks duplicates and matched lazy deletes. | Passed: `g++ -std=c++17 -Wall -Wextra -pedantic tests/test_priority_queue_with_delete.cpp -o /tmp/test_priority_queue_with_delete && /tmp/test_priority_queue_with_delete` |

Deferred:

- Zeta/mobius transforms: not touched because they require missing helper decisions and brace/type cleanup.
- Larger algorithms such as Dinic, FFT, max clique, and dominator tree: left unchanged until there is time for focused stress tests.

## Notebook-Assumption Safe-Fix Pass - 2026-05-15

This pass allows normal ICPC notebook context: common aliases/macros may be
printed with the snippet, and `#define int long long` is acceptable when the
snippet is intended to rely on it.

| Issue | Change | Assumption or macro | Regression test | Result |
|---|---|---|---|---|
| CHT integer width note conflicted with code | Documented that the snippet requires notebook-wide `#define int long long`, changed `inf` to `LLONG_MAX`, and fixed a comment typo. | `#define int long long` is printed before the snippet, so `Line::k/m/p`, `div`, `add`, and `get` are 64-bit. | `tests/test_line_container_macro.cpp` checks min/max queries, equal slopes, and large coefficients against brute force. | Passed: `g++ -std=c++17 -Wall -Wextra -pedantic tests/test_line_container_macro.cpp -o /tmp/test_line_container_macro && /tmp/test_line_container_macro` |
| Dinic depended on missing notebook aliases | Added printable `ll`, `vi`, `sz`, and `rep` definitions above the snippet. | `bits/stdc++.h` and `using namespace std` are available in the notebook template. | `tests/test_dinic_notebook_context.cpp` checks a small max-flow graph, disconnected sink, and zero capacity edge. | Passed: `g++ -std=c++17 -Wall -Wextra -pedantic tests/test_dinic_notebook_context.cpp -o /tmp/test_dinic_notebook_context && /tmp/test_dinic_notebook_context` |
| Suffix cyclic sort indexed `cnt` with possibly signed `char` and crashed on empty input | Added empty-string guard and cast first-character alphabet codes to `unsigned char`. | The algorithm remains cyclic-shifts only; append a unique sentinel before using it as suffix array construction. | `tests/test_suffix_array_cyclic.cpp` compares against brute cyclic sorting for `banana$`, empty string, and high-byte chars. | Passed: `g++ -std=c++17 -Wall -Wextra -pedantic tests/test_suffix_array_cyclic.cpp -o /tmp/test_suffix_array_cyclic && /tmp/test_suffix_array_cyclic` |

Remaining after this pass:

- Virtual tree: LCA insertion/order bug is fixed and covered by `tests/test_virtual_tree.cpp`; still needs extraction from problem-specific DP before printing.
- Zeta/mobius transforms: still need helper decisions and brace/type cleanup.
- FFT mod: dependency is wired to local `fft_v2.cpp`; more random precision testing would still be useful.
- Max clique and dominator tree: keep for a later stress-test pass because they are long and harder to inspect under contest pressure.

## Include-Requested Fix Pass - 2026-05-15

This pass promotes requested snippets toward printable notebook status. Common
notebook macros and nearby dependencies are allowed when they make the snippet
shorter and clearer.

| Snippet | What changed | Assumption/dependency | Test |
|---|---|---|---|
| Line container CHT | Kept as macro-based 64-bit CHT and retained equal-slope/large-value test. | Uses notebook `#define int long long`. | `tests/test_line_container_macro.cpp` |
| Lazy segment tree | Replaced ambiguous guide code with concrete range assignment + range sum using `has_lazy`. | 0-indexed inclusive ranges; adapt `apply/pull` for other ops. | `tests/test_lazy_segment_tree.cpp` |
| FWHT | Replaced pseudocode with C++17 XOR FWHT and convolution helper. | Length must be power of two; modular types need modular inverse in inverse step. | `tests/test_fwht.cpp` |
| FFT mod | Removed missing header include and documented dependency on local `fft_v2.cpp`; added common macros to `fft_v2.cpp`. | Print `fft_v2.cpp` before `fft_mod.cpp`. | `tests/test_fft_mod.cpp` |
| HLD | Added compact range-add/range-max `Node` dependency directly above HLD. | Root is 0; default operations are path/subtree add and max. | `tests/test_hld.cpp` |
| DSU on tree sack | Completed globals, Euler DFS, add/remove helper, and closing braces. | User inserts query answering where marked. | `tests/test_dsu_on_tree_sack.cpp` |
| Kruskal reconstruction tree | Completed edge struct, DSU setup, sorting, internal node weights, and build routine. | Connected graph gives one root; disconnected graph gives a forest. | `tests/test_kruskal_reconstruction_tree.cpp` |
| LCP | Replaced old macro/RMQ wrapper with standard Kasai LCP helper. | Input suffix array must be valid for `s`. | `tests/test_lcp.cpp` |

### HLD `VALS_EDGES`

`VALS_EDGES` selects where path values are stored:

- `HLD<false>`: values are on vertices, so a path query/update includes both endpoints.
- `HLD<true>`: values are on edges, stored at the deeper endpoint of each edge. The LCA vertex is skipped with `pos[u] + VALS_EDGES`, because no edge value belongs to the LCA itself.

Use `HLD<true>` for edge weights and `HLD<false>` for vertex weights.

Full test sweep passed:

```bash
for f in tests/*.cpp; do b=/tmp/$(basename "$f" .cpp); g++ -std=c++17 -Wall -Wextra -pedantic "$f" -o "$b" && "$b" || exit 1; done
```

## Current Problems

These are the main issues remaining before the notebook is genuinely trusted
and printable:

| Area | Problem | Next step |
|---|---|---|
| Zeta/Mobius transforms | `sections/math/zeta_and_mobius.cpp` still has compile/structure issues and depends on an undefined prime enumerator. | Replace or complete with tested subset/divisor/multiple transforms. |
| Virtual tree | Generic builder is fixed, but the file still contains problem-specific color DP. | Extract a clean `build_virtual_tree(keys)` snippet and keep the DP elsewhere or remove it. |
| FFT / FFT mod | Compiles and has a small test, but precision limits are subtle. | Add random convolution stress tests against naive for several mods and coefficient ranges. |
| Line container CHT | Works in tests under `#define int long long`, but relies on global `minimum`. | Consider splitting min/max wrappers or documenting the global flag prominently. |
| HLD | Included `Node` only supports range add + range max. | Add usage note in snippet or provide a simpler process-only HLD variant. |
| Sack | It is a template skeleton; users must insert query answering manually. | Add a tiny usage example with subtree color frequency query. |
| Kruskal reconstruction tree | Build is compile-tested, but query use is not shown. | Add LCA/max-edge threshold usage notes or example. |
| Old/maybe snippets | Gaussian elimination and XOR basis still need focused review/tests. | Review one by one before promoting to final printed notebook. |

Ignored by choice for now: dominator tree, max clique, global min cut, and treap. they should be included. whitout change.
