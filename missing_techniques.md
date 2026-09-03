# Missing technique inventory

This is a documentation-only inventory generated from the technique data at `/home/dedibeat/projects/llm-integration/data/techniques_viewer.html` (3,023 problem rows in the current snapshot). It records techniques that were absent from the dataset's `notebook` taxonomy when generated. Some have since been selected and added to this repository; this file remains the discovery inventory rather than a live completion checklist.

## How to read this

- **Taxonomy extensions** are the dataset’s explicit missing-technique list. “Problems” counts distinct rows with a primary or secondary tag; primary/secondary counts retain the classifier’s role. Median ratings are descriptive, not a recommendation threshold.
- **Extras** are unnormalized tags emitted outside the taxonomy. They are included verbatim so they can be discussed and merged later; spelling variants and aliases are intentionally not collapsed.
- A zero count means the taxonomy names the technique, but this snapshot did not attach it to a row.

## Taxonomy extensions

### data-structures

| Technique | Problems | Primary | Secondary | Median rating | Dataset note |
|---|---:|---:|---:|---:|---|
| `persistent-data-structures` | 23 | 19 | 4 | 2875 | persistent segment tree / array; k-th on prefix, versioned queries |
| `li-chao-tree` | 9 | 7 | 2 | 2938 | line/segment container over fixed x-coordinates |
| `segment-tree-beats` | 2 | 2 | 0 | 2938 | chmin/chmax range updates (Ji Driver segment tree) |
| `merge-sort-tree` | 1 | 0 | 1 | — | values-in-node segment tree for order statistics |
| `2d-data-structures` | 10 | 10 | 0 | 3004 | 2D fenwick / segment tree of structures |
| `sqrt-decomposition` | 34 | 25 | 9 | 2948 | block decomposition of arrays / queries |
| `mo-algorithm` | 3 | 3 | 0 | 3009 | offline query ordering by blocks (incl. Mo on trees, with updates) |
| `link-cut-tree` | 5 | 5 | 0 | 3528 | dynamic trees, path queries under linking/cutting |
| `kd-tree` | 3 | 2 | 1 | 3416 | spatial partitioning for nearest-neighbor / box queries |
| `bitset-optimization` | 46 | 29 | 17 | 2572 | word-parallel speedup of dp / reachability |
| `small-to-large` | 14 | 6 | 8 | 2628 | merging sets/maps by size (outside the tree-sack case) |
| `centroid-decomposition` | 17 | 17 | 0 | 2854 | divide and conquer over tree centroids |
| `wavelet-tree` | 1 | 0 | 1 | 3571 | rank/select/quantile queries over value ranges |
| `top-tree` | 2 | 2 | 0 | 3341 | dynamic tree path+subtree aggregates beyond link-cut |
| `fractional-cascading` | 0 | 0 | 0 | — | shared successor pointers across sorted lists |
| `offline-dynamic-connectivity` | 7 | 7 | 0 | 2892 | edge lifetimes on a segment tree over time + rollback DSU |

### paradigms / offline

| Technique | Problems | Primary | Secondary | Median rating | Dataset note |
|---|---:|---:|---:|---:|---|
| `cdq-divide-and-conquer` | 23 | 19 | 4 | 3120 | offline 3-side dominance / dp with dc over time |
| `parallel-binary-search` | 3 | 2 | 1 | 2370 | binary search all queries simultaneously over one process replay |
| `meet-in-the-middle` | 14 | 13 | 1 | 2711 | split search space in halves, join |
| `ternary-search` | 20 | 17 | 3 | 2858 | unimodal optimization |
| `exchange-argument` | 23 | 19 | 4 | 2186 | greedy ordering proved by adjacent swap |
| `binary-lifting` | 21 | 17 | 4 | 2877 | jump pointers beyond LCA (functional graphs, k-th ancestor variants) |

### graph

| Technique | Problems | Primary | Secondary | Median rating | Dataset note |
|---|---:|---:|---:|---:|---|
| `0-1-bfs` | 5 | 4 | 1 | 3143 | deque shortest path on 0/1 weights |
| `bellman-ford` | 6 | 3 | 3 | 2701 | negative edges / negative-cycle detection, spfa |
| `floyd-warshall` | 12 | 9 | 3 | 2388 | all-pairs shortest paths, transitive closure |
| `minimum-spanning-tree` | 17 | 15 | 2 | 2188 | kruskal / prim / boruvka (plain mst, no krt) |
| `eulerian-path` | 6 | 5 | 1 | 2678 | euler tour / circuit construction |
| `2-sat` | 7 | 6 | 1 | 3023 | implication graph + scc |
| `difference-constraints` | 4 | 4 | 0 | 2701 | system of x_i - x_j <= c as shortest paths |
| `functional-graph` | 20 | 16 | 4 | 2755 | rho-shaped successor graphs, cycle finding |
| `euler-tour-flattening` | 16 | 11 | 5 | 2849 | subtree/path to array interval reduction |
| `hungarian-algorithm` | 3 | 3 | 0 | 2446 | assignment problem (min-cost perfect matching on bipartite) |
| `general-matching` | 2 | 2 | 0 | 2530 | blossom algorithm on non-bipartite graphs |
| `konig-theorem` | 5 | 4 | 1 | 2486 | min vertex cover / max independent set via matching |
| `min-cut-modeling` | 11 | 9 | 2 | 2907 | project selection / closure / profit as s-t min cut |
| `gomory-hu-tree` | 0 | 0 | 0 | — | all-pairs min cuts |
| `directed-mst` | 0 | 0 | 0 | — | chu-liu/edmonds arborescence |
| `tree-hashing` | 9 | 9 | 0 | 2650 | rooted/unrooted tree isomorphism hashing (AHU) |
| `planar-graph-duality` | 10 | 7 | 3 | 2822 | faces, dual graph, planar cut = dual cycle |

### dp

| Technique | Problems | Primary | Secondary | Median rating | Dataset note |
|---|---:|---:|---:|---:|---|
| `bitmask-dp` | 47 | 39 | 8 | 2787 | subsets as states (incl. dp over submasks) |
| `digit-dp` | 14 | 12 | 2 | 2344 | count numbers by digit positions with tight flag |
| `broken-profile-dp` | 6 | 6 | 0 | 2543 | plug/contour dp on grids |
| `rerooting` | 22 | 21 | 1 | 2697 | tree dp evaluated for every root |
| `slope-trick` | 8 | 8 | 0 | 2732 | convex piecewise-linear function maintenance |
| `aliens-trick` | 5 | 5 | 0 | 2956 | lagrangian relaxation / wqs binary search on a constraint |
| `open-close-interval-trick` | 1 | 0 | 1 | 1907 | dp over events opening/closing components |
| `connected-component-dp` | 3 | 3 | 0 | 2164 | dp inserting elements into growing components |
| `matrix-exponentiation` | 16 | 16 | 0 | 2599 | linear recurrence via matrix power (incl. kitamasa) |
| `longest-increasing-subsequence` | 23 | 22 | 1 | 2511 | lis and patience-sorting arguments |

### string

| Technique | Problems | Primary | Secondary | Median rating | Dataset note |
|---|---:|---:|---:|---:|---|
| `suffix-automaton` | 12 | 11 | 1 | 2954 | sam; distinct substrings, occurrence counts |
| `palindromic-tree` | 5 | 5 | 0 | 2906 | eertree; palindromic substring structure |
| `lyndon-factorization` | 4 | 4 | 0 | 3130 | duval; smallest suffix/rotation arguments |
| `suffix-tree` | 1 | 1 | 0 | 3335 | ukkonen; explicit suffix trie structure (distinct from sam) |

### math

| Technique | Problems | Primary | Secondary | Median rating | Dataset note |
|---|---:|---:|---:|---:|---|
| `polynomial-operations` | 20 | 14 | 6 | 3017 | poly inverse / ln / exp / division, multipoint evaluation |
| `berlekamp-massey` | 0 | 0 | 0 | — | shortest linear recurrence from samples |
| `lagrange-interpolation` | 11 | 10 | 1 | 3057 | polynomial reconstruction from points |
| `burnside-polya` | 2 | 2 | 0 | 3093 | counting orbits under group actions |
| `generating-functions` | 38 | 34 | 4 | 2983 | ogf/egf manipulation as the core solution idea |
| `matrix-tree-theorem` | 0 | 0 | 0 | — | spanning tree counting via kirchhoff determinant |
| `lgv-lemma` | 2 | 2 | 0 | 3018 | non-intersecting lattice paths as a determinant |
| `floor-sum` | 9 | 9 | 0 | 3236 | sum of floor((a*i+b)/c) and euclidean-like recursions |
| `matroid` | 4 | 4 | 0 | 2736 | matroid intersection / exchange arguments as stated machinery |
| `lp-simplex` | 1 | 1 | 0 | 3285 | linear programming solved directly |
| `hall-theorem` | 12 | 10 | 2 | 2353 | perfect matching existence via neighborhood condition |
| `sprague-grundy` | 17 | 17 | 0 | 2640 | impartial game values, xor of grundy numbers |
| `lucas-theorem` | 3 | 3 | 0 | 2681 | binomials mod p via digits (incl. kummer) |
| `schreier-sims` | 1 | 1 | 0 | 2786 | permutation group order / membership |

### geometry

| Technique | Problems | Primary | Secondary | Median rating | Dataset note |
|---|---:|---:|---:|---:|---|
| `rotating-calipers` | 8 | 4 | 4 | 3171 | antipodal pair scanning on a hull |
| `half-plane-intersection` | 8 | 8 | 0 | 3224 | intersection of half planes / kernel of polygon |
| `sweep-line` | 67 | 49 | 18 | 3068 | event-ordered scanning (segments, unions of rectangles) |
| `minkowski-sum` | 11 | 11 | 0 | 3209 | polygon sums for distance/feasibility |
| `3d-geometry` | 14 | 13 | 1 | 2876 | 3d vectors, 3d convex hull |
| `delaunay-voronoi` | 2 | 2 | 0 | 2695 | proximity structures |

## Unnormalized extras (all tags)

These 400 tags are data signals, not yet approved notebook entries. Counts are distinct problem rows.

- `inclusion-exclusion` — 31
- `constructive` — 29
- `monotonic-stack` — 25
- `interval-dp` — 24
- `knapsack-dp` — 20
- `topological-sort` — 18
- `two-pointers` — 17
- `tree-dp` — 15
- `backtracking` — 11
- `divide-and-conquer` — 10
- `pigeonhole-principle` — 10
- `trie` — 9
- `angular-sweep` — 8
- `cartesian-tree` — 8
- `monotonic-queue` — 8
- `multi-source-bfs` — 8
- `tree-knapsack` — 8
- `block-cut-tree` — 7
- `euclidean-algorithm` — 7
- `linearity-of-expectation` — 7
- `minimax` — 7
- `reflection-principle` — 7
- `binary-search-on-answer` — 6
- `cactus-graph` — 5
- `coordinate-compression` — 5
- `difference-array` — 5
- `randomized-algorithm` — 5
- `sliding-window` — 5
- `chromatic-polynomial` — 4
- `decision-tree` — 4
- `dfs-tree` — 4
- `extended-euclidean-algorithm` — 4
- `local-search` — 4
- `simulation` — 4
- `biconnected-components` — 3
- `binary-search` — 3
- `bostan-mori` — 3
- `combinatorial-game-theory` — 3
- `constructive-algorithm` — 3
- `exponential-search` — 3
- `gray-code` — 3
- `lp-duality` — 3
- `memoization` — 3
- `stirling-numbers` — 3
- `stirling-numbers-of-the-second-kind` — 3
- `subset-sum` — 3
- `taylor-series` — 3
- `tree-diameter` — 3
- `0-1-principle` — 2
- `2d-binary-search` — 2
- `2d-difference-array` — 2
- `2d-prefix-sum` — 2
- `2d-prefix-sums` — 2
- `arbitrary-precision-arithmetic` — 2
- `barrett-reduction` — 2
- `bezouts-identity` — 2
- `binary-trie` — 2
- `bipolar-orientation` — 2
- `bounded-knapsack` — 2
- `cayley-formula` — 2
- `combinatorics` — 2
- `convex-polygon-dp` — 2
- `dilworths-theorem` — 2
- `ear-decomposition` — 2
- `expected-value-dp` — 2
- `expression-parsing` — 2
- `funnel-algorithm` — 2
- `graph-coloring` — 2
- `graph-degeneracy` — 2
- `greedy` — 2
- `hook-length-formula` — 2
- `huffman-coding` — 2
- `inclusion-exclusion-principle` — 2
- `insertion-sort` — 2
- `integer-partition` — 2
- `integration` — 2
- `interval-cover` — 2
- `interval-scheduling` — 2
- `knapsack` — 2
- `lagrange-inversion` — 2
- `line-container` — 2
- `long-path-decomposition` — 2
- `min-25-sieve` — 2
- `monotone-queue` — 2
- `monotone-stack` — 2
- `numerical-integration` — 2
- `offline-queries` — 2
- `permutation-parity` — 2
- `polar-angle-sorting` — 2
- `potential-method` — 2
- `prefix-sum` — 2
- `prefix-sum-optimization` — 2
- `prufer-code` — 2
- `quicksort` — 2
- `radial-sweep` — 2
- `random-walk` — 2
- `raney-lemma` — 2
- `rsk-algorithm` — 2
- `series-parallel-reduction` — 2
- `splay-tree` — 2
- `sqrt-thresholding` — 2
- `std-set` — 2
- `tournament-graph` — 2
- `trial-division` — 2
- `visibility-graph` — 2
- `young-tableau` — 2
- `0-1-knapsack` — 1
- `0-1-trie` — 1
- `01-trie` — 1
- `1d-kmeans` — 1
- `1d1d-dp-optimization` — 1
- `2d-sliding-window` — 1
- `321-avoiding-permutations` — 1
- `3d-prefix-sum` — 1
- `addition-chain` — 1
- `affine-plane` — 1
- `alternating-path` — 1
- `alternating-permutations` — 1
- `amortized-analysis` — 1
- `augmenting-path` — 1
- `avl-tree` — 1
- `barycentric-coordinates` — 1
- `base-conversion` — 1
- `beam-search` — 1
- `bentley-ottmann` — 1
- `bertrands-ballot-theorem` — 1
- `big-integer` — 1
- `bigint` — 1
- `billiards-unfolding` — 1
- `bin-packing-dp` — 1
- `binary-encoding` — 1
- `binomial-inversion` — 1
- `bipartite-checking` — 1
- `birthday-paradox` — 1
- `bit-manipulation` — 1
- `bit-packing` — 1
- `bitwise-independence` — 1
- `bounded-edit-distance` — 1
- `bounded-search-tree` — 1
- `brainfuck` — 1
- `branch-and-bound` — 1
- `carry-lookahead-adder` — 1
- `cat-tree` — 1
- `chain-decomposition` — 1
- `chebyshev-approximation` — 1
- `chebyshev-distance` — 1
- `chinese-postman-problem` — 1
- `chtholly-tree` — 1
- `circle-intersection` — 1
- `circle-rectangle-intersection` — 1
- `clique-enumeration` — 1
- `coffman-graham-algorithm` — 1
- `complementary-counting` — 1
- `configuration-lp` — 1
- `connected-components` — 1
- `consecutive-ones-property` — 1
- `constraint-propagation` — 1
- `constructive-geometry` — 1
- `convex-bipartite-matching` — 1
- `coppersmith-method` — 1
- `core-decomposition` — 1
- `cornacchia-algorithm` — 1
- `cycle-basis` — 1
- `cycle-dp` — 1
- `cycle-lemma` — 1
- `dag-longest-path` — 1
- `de-bruijn-graph` — 1
- `de-bruijn-sequence` — 1
- `decision-monotonicity` — 1
- `deterministic-finite-automaton` — 1
- `dial-algorithm` — 1
- `differential-equations` — 1
- `differential-poset` — 1
- `dilworth-theorem` — 1
- `dirichlet-hyperbola-method` — 1
- `disjoint-sparse-table` — 1
- `double-logarithm` — 1
- `doubling` — 1
- `doubly-linked-list` — 1
- `dp-on-automaton` — 1
- `dp-on-dag` — 1
- `dulmage-mendelsohn-decomposition` — 1
- `dynamic-convex-hull` — 1
- `dynamic-segment-tree` — 1
- `earliest-deadline-first` — 1
- `edge-coloring` — 1
- `elementary-symmetric-polynomials` — 1
- `entringer-numbers` — 1
- `envy-cycle-elimination` — 1
- `erdos-gallai-theorem` — 1
- `erdos-szekeres-theorem` — 1
- `euler-characteristic` — 1
- `eulers-formula` — 1
- `even-adjacency-split` — 1
- `expectation-dp` — 1
- `exterior-algebra` — 1
- `fermat-little-theorem` — 1
- `fibonacci-word` — 1
- `finite-differences` — 1
- `finite-field` — 1
- `fitch-cheney-card-trick` — 1
- `fixed-point-iteration` — 1
- `floored-division` — 1
- `frobenius-coin-problem` — 1
- `gale-ryser-theorem` — 1
- `girth` — 1
- `gittins-index` — 1
- `golden-section-search` — 1
- `graham-pollak-formula` — 1
- `gram-matrix` — 1
- `greedy-coin-change` — 1
- `greedy-edge-coloring` — 1
- `grid-hashing` — 1
- `halfspace-intersection` — 1
- `ham-sandwich-theorem` — 1
- `hamiltonian-cycle` — 1
- `hamiltonian-path` — 1
- `harmonic-series` — 1
- `havel-hakimi` — 1
- `hensel-lifting` — 1
- `herons-formula` — 1
- `hierarchical-clustering` — 1
- `hilbert-curve` — 1
- `hill-climbing` — 1
- `hirschberg-algorithm` — 1
- `hitting-set` — 1
- `hockey-stick-identity` — 1
- `horner-method` — 1
- `image-processing` — 1
- `information-theory` — 1
- `integer-partition-dp` — 1
- `integer-partitions` — 1
- `integral-cryptanalysis` — 1
- `interactive` — 1
- `inversion-counting` — 1
- `inverted-index` — 1
- `jensen-inequality` — 1
- `josephus-problem` — 1
- `k-core` — 1
- `k-way-merge` — 1
- `k-wise-independence` — 1
- `kadanes-algorithm` — 1
- `karatsuba` — 1
- `karmarkar-karp` — 1
- `karp-min-mean-cycle` — 1
- `kinetic-segment-tree` — 1
- `kkt-conditions` — 1
- `krausz-theorem` — 1
- `lagrange-duality` — 1
- `laminar-family` — 1
- `landau-vishkin-algorithm` — 1
- `largest-inscribed-circle` — 1
- `lateqd` — 1
- `lll-algorithm` — 1
- `logic-synthesis` — 1
- `longest-path-on-dag` — 1
- `longest-previous-factor` — 1
- `lucas-sequence` — 1
- `lucy-dp` — 1
- `maclaurin-series` — 1
- `maekawa-theorem` — 1
- `main-lorentz` — 1
- `manhattan-chebyshev-transformation` — 1
- `manhattan-distance` — 1
- `manhattan-to-chebyshev` — 1
- `markov-decision-process` — 1
- `mastermind` — 1
- `matrix-determinant-lemma` — 1
- `max-cut` — 1
- `maximal-empty-rectangle` — 1
- `maximum-matching-game` — 1
- `median` — 1
- `min-max-inclusion-exclusion` — 1
- `min-plus-convolution` — 1
- `min-plus-matrix-multiplication` — 1
- `minhash` — 1
- `minimax-search` — 1
- `minimum-diameter-spanning-tree` — 1
- `minimum-isolating-cut` — 1
- `minimum-path-cover` — 1
- `mixed-radix` — 1
- `mo-with-rollback` — 1
- `monotone-minima` — 1
- `narayana-numbers` — 1
- `nash-equilibrium` — 1
- `newtons-identities` — 1
- `newtons-method` — 1
- `number-theoretic-chunking` — 1
- `one-instruction-set-computer` — 1
- `optimal-stopping` — 1
- `order-preserving-pattern-matching` — 1
- `outerplanar-graph` — 1
- `parity-check` — 1
- `parking-functions` — 1
- `partition-dp` — 1
- `periodicity-lemma` — 1
- `permutation-graph` — 1
- `perspective-projection` — 1
- `pisano-period` — 1
- `planar-face-traversal` — 1
- `planar-graph` — 1
- `planar-point-location` — 1
- `point-in-polygon` — 1
- `poissonization` — 1
- `polygon-clipping` — 1
- `polygon-triangulation` — 1
- `polynomial-gcd` — 1
- `polynomial-regression` — 1
- `pool-adjacent-violators` — 1
- `posa-rotation` — 1
- `power-projection` — 1
- `pq-tree` — 1
- `precomputation` — 1
- `prefix-doubling` — 1
- `prefix-sums` — 1
- `prefix-xor` — 1
- `prime-factorization` — 1
- `principle-of-inclusion-exclusion` — 1
- `priority-queue` — 1
- `product-automaton` — 1
- `projective-plane` — 1
- `pseudotree` — 1
- `quaternion-group` — 1
- `radewoosh-trick` — 1
- `radial-sort` — 1
- `radix-decomposition` — 1
- `randomization` — 1
- `randomized-lp` — 1
- `range-chunking` — 1
- `ranking-unranking` — 1
- `rearrangement-inequality` — 1
- `recursive-descent-parsing` — 1
- `regret-greedy` — 1
- `regular-expressions` — 1
- `retrograde-analysis` — 1
- `robinson-schnested-knuth` — 1
- `rollback-dp` — 1
- `roots-of-unity-filter` — 1
- `rotating-sweep-line` — 1
- `runs` — 1
- `schwartz-zippel-lemma` — 1
- `seaweed-algorithm` — 1
- `segment-tree-descent` — 1
- `segment-tree-split` — 1
- `segment-tree-splitting` — 1
- `separating-axis-theorem` — 1
- `series-parallel-graph` — 1
- `set-cover` — 1
- `shannon-expansion` — 1
- `shellsort` — 1
- `simd-vectorization` — 1
- `similarity-transformation` — 1
- `simpsons-rule` — 1
- `simulated-min-cost-flow` — 1
- `sliding-token-problem` — 1
- `sliding-window-dp` — 1
- `small-side-d-and-c` — 1
- `smawk` — 1
- `sorting-network` — 1
- `sos-dp` — 1
- `spanning-tree` — 1
- `spatial-hashing` — 1
- `splits-equivalence-theorem` — 1
- `sqrt-dp` — 1
- `stars-and-bars` — 1
- `state-inversion` — 1
- `state-space-bfs` — 1
- `steiner-tree` — 1
- `straight-line-program` — 1
- `string-rewriting-system` — 1
- `subsequence-automaton` — 1
- `surface-topology` — 1
- `surreal-numbers` — 1
- `tensor-decomposition` — 1
- `thue-morse-sequence` — 1
- `timsort` — 1
- `transfer-matrix-method` — 1
- `transitive-orientation` — 1
- `trapezoidal-rule` — 1
- `tree-centroid` — 1
- `tree-compatibility` — 1
- `tree-decomposition` — 1
- `tree-encoding` — 1
- `triangle-enumeration` — 1
- `triangle-finding` — 1
- `trie-dp` — 1
- `trilateration` — 1
- `unfolding-trick` — 1
- `unicyclic-graph` — 1
- `unit-monge-matrix-multiplication` — 1
- `value-iteration` — 1
- `vieta-formulas` — 1
- `walecki-theorem` — 1
- `wallace-tree` — 1
- `weight-balanced-top-tree` — 1
- `weight-balanced-tree` — 1
- `yotei-chouwa-dp` — 1
- `young-lattice` — 1
- `young-tableaux` — 1
- `zero-one-principle` — 1
