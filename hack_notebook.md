# ICPC Practical Tricks Notebook

A focused C++17 companion: practical search/algebra tricks, two Lagrange interpolation variants, and connected-subset centroid counting. Indices are 0-based except SAT's signed 1-based literals and the supplied 1-indexed centroid-counting solution. This booklet is separate from `notebook.tex`.

Copy `sections/hacks/common.hpp` once, then the selected snippet. The PDF prints the shared setup on page 1 and omits local `#include "common.hpp"` lines. Do not use `#define int long long`: `int` is for indices, `long long` for arithmetic, and unsigned 64-bit words for bit operations. Shared modular helpers use the fixed prime 1000000007; do not increase it without checking multiplication overflow. The centroid-counting entry is a standalone program with its own modulus, 998244353.

Seed `mt19937_64` once in `main`, then pass it by reference. Fixed seeds make debugging reproducible; a runtime seed is appropriate for submission. Probability bounds assume independent uniform samples on a fixed input. For Q calls, bound total failure by the sum of the individual failure probabilities. Passing random tests is not a proof of a probability bound.

Exact means the result is correct when the search finishes; it does not promise fast execution. Bounded-error methods have stated mathematical assumptions. A budgeted search returning `nullopt` or `false` means NOT FOUND, unless the entry explicitly promises an exact negative result. Always check the output contract before printing NO.

Build PDF: `python3 tools/build_hack_notebook.py` (requires `reportlab`). Output: `output/pdf/icpc_hack_notebook.pdf`.

Run tests: `bash tools/test_hack_notebook.sh`. Sanitizers: `SANITIZE=1 bash tools/test_hack_notebook.sh`. Assertions must remain enabled. Tests cover all printed code, including the reused Lagrange snippet; their fixed-seed success checks are regression tests, not universal heuristic guarantees.

## 1. Berlekamp-Massey + nth term

**Status:** EXACT UNDER RECURRENCE CONTRACT

**Purpose:** Count walks or finite-state processes at a huge index. Generate initial answers with a slow DP, recover their recurrence, then jump to N.

**Idea:** BM repairs a recurrence when the next sample disagrees. To evaluate it, compute x^N modulo its characteristic polynomial. A fixed linear transition on S states guarantees recurrence order at most S, so 2S samples suffice over this field.

**Code:** sections/hacks/linear_recurrence.cpp

**Complexity:** For s samples: O(s^2 + s log P). For order L: O(L^2 log N) evaluation. O(s + L) memory, plus the cost of generating samples. P = 1000000007.

**Pitfalls:** A recurrence fitting a finite prefix need not predict an arbitrary sequence. Prove an order bound; use at least twice that many samples. Supply at least L initial terms. Empty recurrence denotes the zero sequence. This is modular arithmetic, not integer sequence reconstruction.

**Example:** `auto r = berlekampMassey({0,1,1,2});` then `nthTerm({0,1}, r, 10) == 55`. N is 0-indexed.

**Tests:** Empty/zero sequences, order one, leading zeros, negative coefficients, 1,000 generated recurrences with held-out terms, and huge unsigned indices checked against matrix exponentiation.

**Sources:** [KACTL BM](https://raw.githubusercontent.com/kth-competitive-programming/kactl/main/content/numerical/BerlekampMassey.h); [KACTL recurrence evaluation](https://raw.githubusercontent.com/kth-competitive-programming/kactl/main/content/numerical/LinearRecurrence.h).

## 2. Tutte matrix matching size

**Status:** BOUNDED ERROR / LOWER BOUND

**Purpose:** Find the size of a maximum matching in a general undirected graph, including graphs with odd cycles. This version does not recover matching edges.

**Idea:** Assign each edge an independent random field value r; put r and -r in opposite matrix entries. The symbolic rank is twice the matching size. Random evaluation preserves that rank with high probability; it can only lower it.

**Code:** sections/hacks/tutte_matching.cpp

**Complexity:** O(t n^3) time, O(n^2) memory for t trials. For n < P, failure is at most (n/P)^t; take the maximum result across trials.

**Pitfalls:** Prime P must be odd. Input has vertices 0..n-1 and no self-loops; duplicate edges are harmless here. A result is a lower bound, not a certificate of optimality. Never replace random edge weights by all ones.

**Example:** `tutteSize(3, {{0,1},{1,2},{2,0}}, 3, rng)` returns 1 with high probability.

**Tests:** Every simple graph through 5 vertices versus exhaustive matching; 300 random graphs through 12 vertices; empty graphs, odd cycles, duplicate input edges and disconnected components.

**Sources:** [Randomized general matching with Tutte matrix](https://codeforces.com/blog/entry/92400?locale=en).

## 3. Vertex cover with a small budget

**Status:** EXACT / EXPONENTIAL

**Purpose:** Delete at most k vertices so no conflicting pair remains. Useful when k is small even if n is large. Returns selected vertices, or nullopt if impossible.

**Idea:** Every uncovered edge needs one endpoint selected. Branch on its endpoints. If a vertex has more than k remaining neighbors, selecting it is forced: excluding it would require selecting all those neighbors.

**Code:** sections/hacks/vertex_cover.cpp

**Complexity:** O(2^k (n+m)) time. O((k+1)(n+m)) memory for recursive edge-list copies. Recursion depth is at most k+1.

**Pitfalls:** The graph must be simple and undirected, with valid vertices and no self-loops or duplicate edges. Duplicates break the degree-based forced rule. The result is a cover of size at most k; it is not necessarily minimum. Try budgets in increasing order if a minimum is required.

**Example:** `vertexCover(3, {{0,1},{1,2}}, 1)` returns `{1}`. A present empty vector is a valid solution for an edgeless graph.

**Tests:** Every graph through 5 vertices at all budgets; random graphs versus subset enumeration; k=0, negative budget, isolated vertices, a 100-vertex star, and repeated calls.

**Sources:** [MIT parameterized algorithms notes](https://courses.csail.mit.edu/6.5440/fall23/scribe/lec19.pdf).

## 4. Color-coding for short simple paths

**Status:** BOUNDED ERROR / VERIFIED WITNESS

**Purpose:** Find a simple path containing exactly k vertices in a directed or undirected graph. Returns the vertex sequence; nullopt means not found.

**Idea:** Randomly assign k colors. Subset DP tracks paths with distinct colors, which automatically have distinct vertices. A fixed target path is colorful with probability p = k!/k^k per trial.

**Code:** sections/hacks/color_coding.cpp

**Complexity:** O(t 2^k (n+m)) time, O(2^k n) memory. Miss probability is at most (1-p)^t. The implementation caps k at 15, but practical limits are often far smaller.

**Pitfalls:** k counts vertices, not edges. Budget both the DP memory and the repetitions: p is about 0.0384 for k=5 and 0.000363 for k=10. A failed run does not establish impossibility. Every adjacency index must be valid.

**Example:** `colorfulPath({{1},{2},{}}, 3, 100, rng)` searches for `{0,1,2}`. A request for k=0 returns the empty path.

**Tests:** Small directed graphs versus exhaustive simple-path search, reconstructed edge/uniqueness checks, empty input, k>n, k=1 and zero trials. Fixed seeds make regressions repeatable.

**Sources:** [Alon, Yuster, Zwick: Color-coding](https://www.math.tau.ac.il/~nogaa/PDFS/col5.pdf).

## 5. Bit-parallel LCS length

**Status:** EXACT

**Purpose:** Compute the longest common subsequence length of two byte strings using word-level parallelism. It does not reconstruct the subsequence.

**Idea:** Adjacent DP values differ by at most one. Store those differences as bits. For a character mask M, use X = S | M, Y = (S << 1) | 1, then S = X & ~(X-Y). The answer is popcount(S).

**Code:** sections/hacks/bit_lcs.cpp

**Complexity:** Let w = ceil(|b|/64). Time O((|a|+256)w + |b|), memory O(256w). Use the shorter string as b to reduce mask storage. String lengths and the answer must fit int.

**Pitfalls:** Unsigned wraparound is deliberate. Carry from shifts and borrow from subtraction must cross word boundaries. Do not use signed words. Character masks use unsigned byte indices, including bytes 128..255. This is subsequence, not substring.

**Example:** `bitLCS("banana", "ananas") == 5`; `bitLCS("abc", "ac") == 2`.

**Tests:** Empty strings, all equal/disjoint characters, lengths 63/64/65 and 127/128/129, embedded zero/high bytes, and 1,500 random comparisons against ordinary DP.

**Sources:** [Allison and Dix: A bit-string longest-common-subsequence algorithm](https://www.sciencedirect.com/science/article/pii/0020019086900918).

## 6. Algorithm X with bitmasks

**Status:** EXACT / EXPONENTIAL

**Purpose:** Select rows that cover every required column exactly once: tilings, small puzzles, or compatible configurations. Returns original row indices, or nullopt if impossible.

**Idea:** Pick the uncovered column with the fewest currently compatible rows. Try each of those rows, recurse, and undo the choice. Bitmasks give a short Algorithm X implementation; full Dancing Links is omitted to save space.

**Code:** sections/hacks/exact_cover.cpp

**Complexity:** Exponential search; O(c r) work per node for c columns and r rows. O(c) extra stack/solution space, apart from input. At most 64 columns.

**Pitfalls:** Row bits must lie within the declared columns. Every column is mandatory and must be covered exactly once; this is not ordinary set cover. Zero rows are ignored. Column 63 is supported; avoid evaluating 1ULL<<64. A present empty vector solves zero columns.

**Example:** `exactCover(3, {3,4,5})` returns indices `{0,1}`: row masks 011 and 100 cover 111 without overlap.

**Tests:** Zero columns, impossible columns, duplicate/empty rows, multiple solutions, bit 63, all 64 singleton columns, and 1,000 random instances versus row-subset enumeration.

**Sources:** [Knuth: Dancing links](https://arxiv.org/abs/cs/0011047).

## 7. Posa rotations for Hamiltonian paths

**Status:** HEURISTIC / VERIFIED WITNESS

**Purpose:** Search for a path visiting every vertex exactly once in an undirected graph. Useful for constructive tasks where a found path can be checked. Returns nullopt when the search budget is exhausted.

**Idea:** Extend to a random unused neighbor. When stuck, if the last vertex joins path[i], reverse the suffix after i. The same vertices form a valid path with a new endpoint, which may allow further extension.

**Code:** sections/hacks/posa_path.cpp

**Complexity:** O(R (B+1) n) time for R restarts and B extension/rotation steps per restart, on a simple graph. O(n) extra memory. No general success guarantee.

**Pitfalls:** Adjacency must be symmetric with valid indices, no loops or duplicates. Suffix reversal is invalid in general directed graphs. It finds a path, not necessarily a cycle: check the closing edge separately. Failure is NOT FOUND, not NO.

**Example:** `posaPath({{1},{0,2},{1}}, 20, 100, rng)` searches for `{0,1,2}` or its reverse. Verify n distinct vertices and every consecutive edge.

**Tests:** Exhaustive small undirected graphs checked by brute-force Hamiltonian search; every returned witness checked; planted paths in larger graphs; empty/singleton/disconnected inputs and zero-step budgets.

**Sources:** [Ruskey: Combinatorial Generation, section 5.13](https://page.math.tu-berlin.de/~felsner/SemWS17-18/Ruskey-Comb-Gen.pdf).

## 8. Shuffled window subset sum

**Status:** HEURISTIC / ONE-SIDED DECISION

**Purpose:** Search for a subset of nonnegative weights summing exactly to target when full target-sized DP is too large. true proves reachability; false means NOT FOUND. No subset reconstruction.

**Idea:** Greedily form a base subset <=target. Its selected weights become negative removal steps; the others become positive addition steps. Shuffle these signed corrections and run packed subset DP inside [-W,W]. Each step is used at most once.

**Code:** sections/hacks/window_subset_sum.cpp

**Complexity:** O(t n ceil((2W+1)/64)) time, O(n+W/64) memory. W controls resources, not a proven success probability. With W at least the sum of all weights, no state is clipped, but the speed advantage disappears.

**Pitfalls:** Weights and target must be nonnegative signed 64-bit values. The code requires 0<=W<=(INT_MAX-1)/2, and available memory imposes a much smaller limit. Large useful corrections can leave the window and return later; clipping loses them. Repetition does not fix every too-small window.

**Example:** `windowSubset({4,7,9}, 11, 20, 10, rng)` is true. For `{6,10}`, target 10 and W=3, the greedy residual is outside the window: false despite a solution.

**Tests:** Packed operations versus independent byte DP using identical shuffle seeds, full-window equivalence to exact subset DP, no false positives against exact DP, 64-bit shift boundaries, zeros and LLONG_MAX.

**Sources:** [Knapsack, Subset Sum and the (max,+) Convolution](https://codeforces.com/blog/entry/98663?locale=en&mobile=true).

## 9. Schoning randomized 3-SAT

**Status:** BOUNDED ERROR / VERIFIED WITNESS

**Purpose:** Find a satisfying assignment for clauses of at most three literals. A returned vector contains 0/1 variable values; nullopt means no witness was found within the budget.

**Idea:** Start from a uniform random assignment. Find an unsatisfied clause and flip a uniformly chosen literal's variable. After 3n flips, restart. An empty clause is an immediate contradiction; an empty formula is satisfied.

**Code:** sections/hacks/schoning_sat.cpp

**Complexity:** O(R n m) time for R restarts, n variables and m clauses; O(n) extra memory. For satisfiable formulas, success per restart is at least (3/4)^n, so miss probability is at most (1-(3/4)^n)^R. This can require exponentially many restarts.

**Pitfalls:** Literal +(v+1) means x[v]; -(v+1) means not x[v]. Literal 0 is invalid. Clauses contain at most three literals. Timeout cannot certify UNSAT. The implementation deliberately scans clauses; maintaining occurrence lists is a problem-specific optimization.

**Example:** `schoning(2, {{1,2},{-1,2}}, 100, rng)` finds an assignment with x[1]=1. Check every clause before using a witness.

**Tests:** Exhaustive truth-table checks for 500 small random formulas, unit clauses, contradictions, duplicates, tautologies, empty clause/formula, zero restarts, and witness validation.

**Sources:** [Schuler, Schoning, Watanabe: An Improved Randomized Algorithm for 3-SAT](https://www.cs.ubc.ca/~hutter/previous-earg/EmpAlgReadingGroup/schuler01improved.pdf).

## 10. Consecutive-point Lagrange interpolation

**Status:** EXACT UNDER POLYNOMIAL CONTRACT

**Purpose:** Evaluate a polynomial f at a huge or negative x from y[i]=f(i), 0<=i<n. Useful for polynomial sums and counting formulas with a proven degree bound.

**Idea:** Lagrange's i-th term is y[i] times the product of (x-j) over j!=i, divided by i! (n-1-i)! (-1)^(n-1-i). Prefix and suffix products make each numerator O(1); inverse factorials handle denominators.

**Code:** sections/math/lagrange_interpolation.cpp

**Complexity:** O(n + log P) time and O(n) memory per evaluation; P = 1000000007. Reuses the main notebook's existing implementation without modifying it.

**Pitfalls:** Prove degree(f)<n and require n<P. Samples are specifically at 0,1,...,n-1; use the next entry for arbitrary x-coordinates. x and y are interpreted modulo P. A sampled x returns y[x] directly. Empty input returns 0 by implementation convention, not a uniquely determined polynomial.

**Example:** `lagrangeConsecutive({0,1,4}, 10) == 100`. For sum(1..x), samples `{0,1,3}` describe a degree-2 polynomial.

**Tests:** Existing 4,000 random-polynomial tests against direct evaluation; additional empty/constant cases, negative samples, LLONG_MIN/MAX, sample indices, and x congruent to a sample modulo P.

**Sources:** [Local derivation](sections/math/lagrange_interpolation.md); [Existing tests](tests/test_lagrange_interpolation.cpp).

## 11. General Lagrange interpolation

**Status:** EXACT UNDER POLYNOMIAL CONTRACT

**Purpose:** Evaluate f(at) from arbitrary sample pairs (x[i], y[i]), assuming degree(f)<n. Coordinates may be unsorted, negative, or widely spaced. All arithmetic is modulo P=1000000007.

**Idea:** The i-th basis polynomial is the product of (at-x[j])/(x[i]-x[j]) over j!=i. It equals 1 at x[i] and 0 at the other sample points. Sum y[i] times these basis polynomials; modular inverses implement division.

**Code:** sections/hacks/lagrange_general.cpp

**Complexity:** O(n^2 + n log P) time per evaluation, with n modular inverses. For this fixed prime, this is quadratic in n. O(n) memory for normalized input copies. Prefer the previous O(n+log P) version when x[i]=i.

**Pitfalls:** x and y must have equal nonzero length. x residues must be pairwise distinct modulo P: 1 and P+1 collide. Invalid input returns nullopt, even for repeated pairs with identical y. A valid zero result is a present optional containing 0. Normalize before subtraction to avoid overflow for extreme signed inputs. Prove the degree bound; more than one higher-degree polynomial can fit the same samples.

**Example:** `lagrangeGeneral({-1,2,4}, {1,4,16}, 3)` contains 9 (f(x)=x^2). Check the optional before dereferencing. A query at a sample point returns its normalized y; duplicate validation still runs.

**Tests:** Empty/mismatched arrays, singleton/zero polynomials, repeated coordinates modulo P, sample-point queries, LLONG_MIN/MAX coordinates and values, permutation invariance, and 1,500 random polynomials checked by direct Horner evaluation and the consecutive-point implementation.

**Sources:** [Lagrange basis derivation](sections/math/lagrange_interpolation.md); [General interpolation tests](tests/test_lagrange_general.cpp).

## 12. Connected subsets with one centroid

**Status:** EXACT / COMPLETE SOLUTION / 1-INDEXED

**Purpose:** Count connected vertex subsets with exactly one centroid, modulo 998244353. Supplied complete solution; formatting only. Includes its own main and setup.

**Idea:** dp1[v][k] counts k-vertex subsets containing v on its child side; dp2[v][k] counts those containing its parent on the other side. Subtract equal-size pairs across edges from the total: each two-centroid subtree has one balanced edge.

**Code:** sections/hacks/unique_centroid_subsets.cpp

**Complexity:** O(n^2) time. For sibling sizes a,b, their rerooting loops cost O(a min(a,b)) <= O(ab). Each vertex pair belongs to different child subtrees only at its LCA, so these products sum to O(n^2). Downward merges and subtree-size scans also total O(n^2). The two fixed DP arrays occupy about 145 MB (138 MiB).

**Pitfalls:** 1-indexed tree, 1<=n<=3000. Recursive DFS needs sufficient stack. Keep the reset order and g[v].clear(). Do not disable stream synchronization: cin and scanf are mixed. Centroid means component-size balance, not distance center.

**Example:** Input: `1`, then `3`, then edges `1 2` and `2 3` (one item/edge per line). Output: `4` (three singletons and the full path).

**Tests:** Exhaustive labeled trees through n=5, random small trees versus connected-subset enumeration with direct centroid checks, and paths/stars at n=3000 interleaved with tiny cases to check resets.

**Sources:** User-supplied solution; [centroid characterization, Lemma 3.2](https://dwest.web.illinois.edu/pubs/root3rec.pdf); [black-box tests](tests/test_unique_centroid_subsets.py).
