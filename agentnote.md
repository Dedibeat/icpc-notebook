# ICPC notebook: agent notes and next changes

Updated 2026-09-05. Working guidance and suggestions, not an instruction to
implement the entire backlog. Follow [AGENTS.md](AGENTS.md).

## Objective and confirmed preferences

Build a short, trusted, printable C++17 reference for an East Asia regional
team targeting gold or better. Optimize for successful contest use, not coverage.

- **Require less unstated knowledge.** Explain what an operation means and how
  its result solves the problem. Dependencies are welcome when they save space
  or simplify code; name them and make them easy to locate.
- **Choose the representation per technique.** Familiar basics: short idiom.
  Reusable structure: concrete default with a small customization block.
  Modeling technique: compact worked solution.
- **Genericity must earn its space.** Lazy segment tree is the positive example.
  Mo should be a direct distinct-values solution, not a callback framework.
  Do not generalize that preference into removing every abstraction.
- **Keep explanations compact.** Prefer one recognition cue, one essential
  invariant/formula, and one example. Avoid repeated descriptions, API prose,
  long derivations, and explaining ordinary C++.
- **Separate usage blocks are good.** Keep the implementation clean. Show complete
  adaptations when changing only one expression would be unsafe.
- **Preserve contracts when shortening.** Bounds, identities, composition order,
  overflow, resets, cycle handling, and degeneracies must stay visible.
- **Work in small batches and obtain feedback.** Review actual implementations
  first; do not infer their contents from names or old README descriptions.
- **Tests and familiarity are different.** Passing tests does not make a technique
  practiced. Do not label a teammate ready without their input.

## What the trials established

| Entry | Accepted direction | Remaining refinement |
|---|---|---|
| [Lazy segment tree](sections/data_structures/lazy_segment_tree.cpp) | Keep the marked customization block; separate tested add/min and assign/sum examples. Empty-vector initialization was fixed. | Shorten prose in its [usage notes](sections/data_structures/lazy_segment_tree.md); preserve identities and tag order. |
| [Topological sort](sections/graph/topological_sort.cpp) | DFS lambda with cycle detection. | Already compact. A DAG-only version can be shorter, but is a different contract. Do not claim the current DFS version is substantially shorter than Kahn. |
| [Mo](sections/data_structures/mo_algorithm.cpp) | Direct distinct-count solution, local frequency updates, three-line usage block. | Use this as the example-first pattern; do not restore generic callbacks by default. |
| [Block-cut tree](sections/graph/block_cut_tree.md) | Tiny transformation diagram, meaning of block nodes, complete forbidden-vertex [query solution](sections/graph/block_cut_tree_example.cpp) using DSU/LCA. | Explanation compacted and verified with the existing brute-force query stress test and PDF render. |

## Suggestions for existing techniques

P1 = next focused improvements; P2 = later, after feedback. These are source-based
suggestions, not a completed correctness audit of every notebook entry.

| Priority / entry | Observation | Suggested change |
|---|---|---|
| Done [FPS](sections/math/formal_power_series.cpp), [notes](sections/math/formal_power_series.md) | Inverse/log/exp exist; the previous missing bridge was the problem-to-coefficient step. | Completed with coefficient/truncation semantics and an ordered-composition example via `1/(1-P(x))`; retain the constant-term restrictions and exact usage test. |
| Done [Minkowski sum](sections/geometry/minkowski_sum.cpp) | Polygon normalization and angular edge merge were separate from the requested sequence operation. | Completed as the separate [concave max-plus entry](sections/geometry/max_plus_convolution.cpp), with the slope-merge invariant, upper-chain interpretation, and brute-force stress test. |
| P1 [Slope trick](sections/dp/slope_trick.cpp) | Operations and heap representation are documented; the problem-to-DP step is missing. | Keep the structure. Add one solution minimizing movement cost with bounded changes: derive `newF(x)=abs(x-a[i])+min F(y)` over the allowed interval, then show the exact `shift`/`addAbs` order and initialization. Brute-force small integer domains. |
| P1 [Aliens/WQS](sections/dp/aliens_trick.cpp) | Generic wrapper leaves the difficult penalized solver to the caller. | Use one exact-count DP with the penalized recurrence, cost/count tie rule, penalty bounds, and answer recovery in the same example. Keep the discrete-convexity requirement; monotone chosen count alone is insufficient. Compare all small feasible counts with ordinary DP. |
| P1 [Centroid decomposition](sections/graph/centroid_decomposition.cpp) | Builds centroid parents, but implements no query application. | Add a mark-only nearest-marked-vertex solution: maintain the best distance at centroid ancestors; reuse LCA or precompute distances. Print the resulting complexity for the chosen version, not an assumed O(log n). Test no marked vertices, repeated marks, chains, and stars. |
| P1 [Parallel binary search](sections/misc/parallel_binary_search.cpp) | Callback wrapper hides the replay state and event-prefix interpretation. | Prefer a direct first-prefix threshold solution. Keep initial-prefix and never-true cases explicit. Its existing test has a range-sum threshold scenario that can seed the example. |
| P2 [Rerooting](sections/graph/rerooting.cpp) | Useful sum-of-distances default and customization block already exist. | Keep them. Explain `{size,sum}` and the edge transfer in a few lines; show how to read `answer[v].sum`. Fix usage to use `auto` or `Rerooting::DP`, since `DP` is nested. Add another configuration only if requested and tested. |
| P2 [Virtual tree](sections/graph/virtual_tree.cpp) | Returns vertices and parent-child edges, with a reverse-order DP hint. | Add one marked-pair distance solution using compressed edge lengths and subtree marked counts. Explain added LCAs and resetting touched state; test duplicate/empty keys. Do not describe this file as still containing the old problem-specific DP. |
| P2 [DSU on tree](sections/graph/dsu_on_tree_sack.cpp) | Color-frequency state exists, but `answer(v)` is empty. | Complete a subtree distinct-color example, with insertion/removal and full reset. Briefly explain exactly what state exists when the answer is recorded. |
| P2 [CDQ dominance](sections/graph/cdq_dominance.cpp) | Already a concrete 3D counting solution. | Keep this form. Add a tiny example explaining OTHER points, equality, duplicate grouping, and why Fenwick changes are undone. Avoid a generic CDQ framework. |
| P2 [Offline connectivity](sections/graph/offline_dynamic_connectivity.cpp) | Handles add/remove/query events with rollback; one active copy per edge. | Show a short event timeline and returned answers. Explain edge lifetimes and unmatched/duplicate edge restrictions; do not imply multiset-edge support. |
| P2 [Persistent segment tree](sections/data_structures/persistent_segment_tree.cpp) | Prefix-root usage is almost complete, but the loop is pseudocode and answers are compressed ranks. | Print a small compilable compression/build/query/decompression block. Preserve half-open ranges and 1-based k. |
| P2 [Fast knapsack](sections/dp/fast_knapsack_subset_sum.cpp) | Multiple specialized methods and separate derivations. | Add a compact selector: reachability, minimum item count, or maximum value. Give the less familiar residue-window method one small worked case; trim repeated derivations. |
| P2 [D&C DP](sections/dp/divide_and_conquer_dp.cpp), [Knuth](sections/dp/knuth.cpp) | Already concrete partition/merge examples. D&C's printed metadata incorrectly says 0-indexed and leaves cost unimplemented; code is 1-indexed with squared-sum cost. | Preserve example form; reconcile notes and code. State nonnegative-weight assumptions for these examples. Add brute-DP tests before treating them as trusted. Review Knuth's large fixed quadratic allocation and reset assumptions. |
| Done [SAM](sections/string/suffix_automaton.cpp), [eertree](sections/string/palindromic_tree.cpp), [Aho](sections/string/Aho.cpp) | Added tiny examples with expected counts, SAM state-length meaning, eertree roots/links and occurrence finalization, and Aho's duplicate/build behavior. | Retain the lowercase-only and no-insertion-after-finalization contracts. Focused tests passed after the comment pass. |
| P2 [Matching](sections/graph/matching.cpp), [min-cut recipes](sections/graph/min_cut_modeling.md) | Matching has a Konig equality note; min-cut notes already describe weighted-cover extraction. | Add alternating-path extraction of an unweighted cover only if useful; cross-reference existing cut recipes. Test repeated matching calls and brute-force small graphs. Do not list Konig as wholly absent. |
| P2 [Implicit treap](sections/data_structures/treap.cpp) | Raw node fields and split/merge leave allocation and initialization to the reader. | Add safe node initialization and one sequence-reversal example. Test empty/singleton intervals, split endpoints, and repeated operations before printing as trusted. |
| P2 [Geometry routines](sections/geometry/convex_hull.cpp), [HPI](sections/geometry/half_plane_intersection.cpp) | Shared primitives are useful; contracts differ across operations. | Keep dependencies. Add only essential recognition/usage details: orientation, boundary policy, squared distance, boundedness. For HPI, one clipping/feasibility example should explain the bounding box. |

Basic DSU, Fenwick, sparse table, BFS, and similar entries should receive small
contract/example fixes as needed, not blanket rewrites or new wrappers.

## Long implementations to review for compaction

Lengths below are current source lines, including comments/blanks; they are not
printed-page estimates. Aim to reduce copied logic and page use, not line count
by packing statements. Measure the rendered result and retest every code change.

| Entry / lines | Concrete compaction opportunity | Keep or verify |
|---|---|---|
| [Dominator example](sections/graph/critical_cities_dominator.cpp) / 193 | Largest file: includes a generic path-min tree class, program I/O, and tutorial comments. First decide whether to retain it. If retained, extract the needed dominator result and compact the supporting path-min implementation. | Existing LCA is not a drop-in path-min replacement. Test unreachable vertices and targets before shortening; the source itself warns about unreachable-target UB. |
| [Geometry bundle](sections/geometry/convex_hull.cpp) / 133 | This is many routines, not a 133-line hull. Give routines selectable listing ranges/subentries and print only the selected set; share Geometry Base. | Splitting files alone saves no pages. Retain orientation, degeneracy, and boundary contracts for each selected routine. |
| [Offline connectivity](sections/graph/offline_dynamic_connectivity.cpp) / 93 | Try a direct event-processing solution with local interval/DFS helpers; remove convenience wrappers if they add more than they clarify. Factor rollback DSU only if another printed entry reuses it. | Snapshot rollback, unmatched-removal checks, and lifetime endpoints are essential. Ordinary path-compressing DSU is not a replacement. |
| [Fast knapsack bundle](sections/dp/fast_knapsack_subset_sum.cpp) / 92 | Select the needed variants using a short decision table; avoid printing every specialized implementation by default. Share positive-value compression. | Reachability, minimum items, and maximum value have different transitions; do not hide them behind a clever generic DP. |
| [Min-cost flow](sections/graph/min_cost_flow.cpp) / 87 | Trim repeated setup/comments and inspect whether the interface needs every helper. A nonnegative-initial-cost specialization can omit Bellman-Ford initialization if explicitly chosen. | That specialization changes the contract. Preserve potentials, residual-edge bookkeeping, sent-flow checks, and overflow limits. |
| [Sqrt decomposition](sections/data_structures/sqrt_decomposition.cpp) / 73 | Its generic add/sum machinery overlaps lazy segment tree. Trial a short concrete block-decomposition example with explicit partial/full-block loops. | This is a candidate for the Mo treatment, not a mandate to remove useful genericity. Keep partial-block push/rebuild correct. |
| [Aho](sections/string/Aho.cpp) / 72 | Compact the two transition-initialization cases in BFS and repeated traversal boilerplate after reviewing the full build logic. | Preserve missing-edge/failure transitions, root behavior, duplicate counts, and the no-insertion-after-build contract. |
| [Trie bundle](sections/string/trie.cpp) / 69 | Character and XOR tries are distinct tools; label/select them separately. Character word/prefix queries may share traversal if it actually reduces code. | Do not force both alphabets into a generic trie. Preserve multiplicity and deletion rules. |
| [Implicit treap](sections/data_structures/treap.cpp) / 65 | Use the standard split-by-count form to eliminate the absolute `add` offset; move traversal/output to usage. Compact trivial helpers and add a safe node constructor. | Fix/test empty reversal and root ownership before polishing. Preserve push-before-descent and pull-after-change. |
| [Lazy segment tree](sections/data_structures/lazy_segment_tree.cpp) / 64 | Trim duplicate metadata, long divider comments, and redundant prose first. | Preserve the praised customization block and public range wrappers. Do not merge update/query into an opaque recursive framework. |
| [Dinic](sections/graph/dinic_2.cpp) / 63 | Compare the capacity-scaling outer loop with a plain BFS/DFS version; remove repeated macro setup if the shared template supplies it. Keep optional flow/cut helpers together. | Replacement needs correctness and performance tests. Cut recovery is already used by modeling snippets; do not remove that capability silently. |
| [HLD](sections/graph/heavy_light_decomposition.cpp) / 61 | Already reuses SegTree and centralizes chain traversal. Compact its long header and usage rather than rewriting the core. | Keep edge/vertex semantics and conversion from half-open chain intervals to inclusive SegTree ranges visible. |
| [Block-cut builder](sections/graph/block_cut_tree.cpp) / 59 | Small helpers and duplicated description offer modest savings; shorten the accepted explanation first. | The edge stack and parent edge IDs are essential for correct blocks and parallel edges. Do not replace the builder just to save a few lines. |

FPS, SAM, eertree, and wavelet tree should receive modest presentation cleanup;
most of their code represents actual operations. Link-cut, beats, and simplex
already pack substantial logic into dense lines: further minification can make
manual copying worse. For these, reduce optional functionality only after a
team decision, or reconsider inclusion. Shorter source can still print wider,
wrap more, and occupy more space.

Suggested compaction order: repeated notes/metadata; geometry/knapsack bundle
selection; treap after correctness tests; concrete sqrt/offline examples; only
then contract-changing flow specializations. Keep this separate from the next
learning-example batch so feedback remains easy to interpret.

## What is missing now

Checked against current `sections/`, `notebook.tex`, and representative tests.
The historical [missing_techniques.md](missing_techniques.md) is a discovery
inventory, not a live checklist. Its dataset counts do not establish East Asia
regional frequency or justify adding everything.

### Missing applications or variants of existing tools

- **Requested max-plus convolution:** implemented in
  [max_plus_convolution.cpp](sections/geometry/max_plus_convolution.cpp) as a
  separate concave-sequence entry. Polynomial convolution remains a separate
  operation.
- **FPS modeling:** the inverse/log/exp implementation now has a generating-function
  bridge through the ordered-composition example in
  [formal_power_series.md](sections/math/formal_power_series.md). Polynomial
  division and multipoint evaluation remain separate missing operations.
- **Lower/upper-bound flow and circulation:** no complete reduction found.
  Candidate: a compact demand-balance example reusing Dinic, with feasible-flow
  recovery and infeasible cases. Distinguish feasibility from min/max s-t flow.
- **Fast linear-recurrence evaluation:** matrix power exists; no dedicated
  Kitamasa/Bostan-Mori or Berlekamp-Massey implementation found. Choose one
  evaluation method first if practice exposes the need; discovering a recurrence
  is a separate task.
- **Offline 2D point-update/rectangle-query structure:** no dedicated compressed
  2D Fenwick found. CDQ dominance and rectangle-union area cover different tasks.
  Add only for a concrete operation set; test ties and compression boundaries.
- **Li Chao with segment-restricted insertion:** absent. Existing line container
  already covers whole-line extrema, so a second structure should justify its
  extra capability. Specify coordinate domain and use safe evaluation arithmetic.

### Missing compact learning examples or formulas

These are candidates, not an approved expansion batch.

| Candidate | Small useful form | Inclusion condition |
|---|---|---|
| Profile DP | Domino tiling on a narrow board; one mask transition example. | Team practices mask meaning and transitions; defer general plug DP. |
| Small-to-large merging | One map/set subtree aggregation example. | Useful if simpler than the existing sack solution for the chosen task. |
| Burnside counting | One rotation-orbit count with fixed-point counts. | Include when the group action can be explained and modular division is valid. |
| Matrix-tree theorem | Laplacian minor plus modular determinant. | Add and test determinant handling; current modular Gaussian solver does not return it. |
| Probability/expectation | One state recurrence with terminal states and self-loops. | Select a practiced problem; avoid an abstract probability framework. |
| 3D geometry primitives | Dot/cross, line/plane intersection with explicit degeneracy policy. | Only if team practice warrants it; do not bundle a 3D hull automatically. |

Do **not** automatically add blossom, directed MST, Gomory-Hu, top trees,
KD-trees, suffix trees, Delaunay, or advanced group algorithms. They are absent
candidates with additional learning/testing cost, not mandatory gold-medal tools.
Likewise, re-evaluate the space spent on existing dominators, max clique, link-cut,
beats, simplex, and simulated annealing against actual team use before expanding.
No deletion is implied by this note.

### Missing trust and navigation information

- A live entry-to-test map and team practice status. Record implementation evidence
  separately from `unpracticed / practiced / contest-used`; let teammates supply
  familiarity. Many techniques are now implemented despite old README warnings.
- Dedicated test coverage needs verification for treap, Kuhn matching, D&C DP,
  Knuth, global min-cut, dominators, max clique, and CRT. The current filename
  reference scan found no direct test reference for these; that is a lead for
  review, not proof that no indirect/external test exists.
- A compact task-to-entry index: e.g. forbidden vertex -> block-cut, marked subset
  of a tree -> virtual tree, changing a root -> rerooting. Add dependency page
  references and conspicuous interval/k-index conventions where they vary.
- A clear separation of current facts from historical notes in README and the
  gap inventory. Example: old claims about missing suffix-array wrappers or
  broken transforms must be checked against current code before being repeated.

## Focused batch completed - 2026-09-05

| Entry | Completed work | Evidence |
|---|---|---|
| Block-cut tree | Shortened the accepted explanation while keeping the diagram, path test, endpoint handling, disconnected handling, and recursion warning. | `tests/test_block_cut_tree_example.cpp` passed, including random graphs, parallel edges, isolates, repeated queries, and every `(u,v,x)` triple. |
| Formal power series | Added coefficient/truncation definitions and a positive-part ordered-composition example: `fps_inv(1-P,n+1)` and read coefficient `n`. | `tests/test_formal_power_series.cpp` and the exact fenced usage compiled and passed through `tests/test_notebook_examples.py`. |
| Concave max-plus convolution | Added `sections/geometry/max_plus_convolution.cpp` and a separate printable entry. It merges the nonincreasing first differences in linear time and asserts its concavity/output contract. | `tests/test_max_plus_convolution.cpp` passed ties, negatives, empty/length-one inputs, near-limit values, invalid-concavity fixtures, and 3,000 brute-force random cases. |
| Print | Rebuilt `output/pdf/notebook-review.pdf` with LuaLaTeX and inspected the block-cut, FPS, and max-plus pages. | 70-page PDF generated without LaTeX errors; affected pages had no clipping or unreadable overflow. |

The complete `tests/test_*.cpp` sweep passed under `-std=c++17 -O2 -Wall -Wextra -pedantic` (93 tests); the standalone `tests/cses_download_speed.cpp` solution also compiled. Existing user changes in `template.cpp` and the earlier accepted batch were preserved.

## Selective API comment pass completed - 2026-09-05

The earlier broad trailing-comment pass was refined after feedback. Mechanical
`// Expects ...; returns ...` annotations were removed from function signatures.
Reusable structures instead have one compact header-level API model: what each
operation changes or observes, the important invariant or failure convention,
and a tiny example with its expected value. Constructors, obvious getters, and
ordinary C++ are not narrated.

All public index/value intervals now state their endpoint convention explicitly,
including `[l,r)`, `[l,r]`, `[lo,hi)`, and the inclusive position domain of the
mergeable segment tree. Graph paths are described separately as endpoint-inclusive
paths rather than called ranges. Examples were added or clarified for DSU,
Fenwick, lazy/sqrt/beats/persistent segment trees, wavelet tree, link-cut tree,
tries, Aho, eertree, SAM, LCA, SCC, flow structures, offline connectivity, slope
trick, and XOR basis.

`tests/test_notebook_examples.py` and 24 focused C++ tests passed after the
refinement. `output/pdf/notebook-review.pdf` was rebuilt to 71 pages and the
affected data-structure, string, graph, math, and DP pages were visually checked
for clipping, wrapping, and section breaks.

Follow-up: confusing stateful interfaces now use separate, executable usage
blocks instead of expanding their implementation headers. Added blocks cover
persistent prefix roots with compression/decompression, link-cut operations,
Aho/eertree/SAM build-finalize order, and offline-connectivity event timelines.
Meaningful input/output comments remain on full-solution snippets (block-cut
queries, D&C DP, Knuth, and dominators). The exact fenced examples are compiled
by `tests/test_notebook_examples.py`; keep that requirement for future blocks.

Second follow-up: stateful APIs now use labeled `Input`, `Effect`, and `Output`
contracts where mutation or return encoding is non-obvious. Usage blocks label
their concrete input and expected values instead of scattering unexplained
numeric comments. Added `tools/grader.py` and `tools/test.sh` from the team's
local workflow; the latter now stops on compile failure instead of possibly
running a stale executable. Both are printed in Misc and documented in README.
Script syntax/help/fail-fast checks and all fenced-example tests passed. The
73-page PDF was rebuilt and the changed example/tool pages were visually checked.

## Editing and print rules for the next agent

1. Read the target code, printed entry, dependency interfaces, and tests.
2. Before coding, state contest value, edge cases, and files to edit.
3. For unfamiliar material, draft the smallest problem-to-answer example first.
   Fit the explanation around that example; keep longer proofs in practice notes.
4. Default to a few sentences plus one small example. Add a diagram only when it
   replaces explanation. Keep short examples together; avoid excessive blank space.
5. Print complexity, essential pitfalls, and dependencies once where practical;
   avoid repeating identical metadata in LaTeX, comments, and adjacent notes.
6. Compile the exact printed usage/adaptation. Stress changed algorithms against
   brute force, including resets and degenerate cases; reuse existing tests.
7. Build and inspect affected PDF pages. Keep source and printed contracts aligned.
8. Present a small batch for feedback. Preserve unrelated work, including the
   existing user changes in `template.cpp`.

Suggested next batch: gather team feedback on the new examples, then choose one
remaining P1 item for a similarly small, tested learning-example pass. Address
identified test/contract gaps alongside affected entries; do not bulk-add the
missing inventory. This note itself changes documentation only.
