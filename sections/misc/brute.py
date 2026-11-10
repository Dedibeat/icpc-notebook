# Python brute-force recipes for tiny stress-test oracles.
from itertools import combinations, combinations_with_replacement
from itertools import permutations, product


# Executable examples: python3 brute.py --examples
# N length-k tuples: O(N*(k+1)) time, plus checking each candidate.
# Iterators keep input pools; list() below also stores ALL output.
# k >= 0; k=0 gives one empty tuple; k>n gives none without reuse.
# Equal values at different positions stay distinct. Iterators are single-use.
def examples():
    a, k = [10, 20, 30], 2
    pairs = list(combinations(a, k))             # C(n,k), order ignored
    assert pairs == [(10, 20), (10, 30), (20, 30)]
    indices = list(combinations(range(len(a)), k))
    assert indices == [(0, 1), (0, 2), (1, 2)]

    orders = list(permutations(a))              # n! full orders
    assert len(orders) == 6
    ordered_pairs = list(permutations(a, k))    # n!/(n-k)!
    assert ordered_pairs == [(10, 20), (10, 30), (20, 10),
                             (20, 30), (30, 10), (30, 20)]
    repeated = list(combinations([1, 1, 2], 2))
    assert repeated == [(1, 1), (1, 2), (1, 2)]
    unique = sorted(set(permutations([1, 1, 2])))  # still generates n! tuples!
    assert unique == [(1, 1, 2), (1, 2, 1), (2, 1, 1)]

    bits = list(product(range(2), repeat=3))    # 2**3 bit strings
    assert len(bits) == 8 and bits[-1] == (1, 1, 1)
    words = [''.join(s) for s in product('ab', repeat=2)]
    assert words == ['aa', 'ab', 'ba', 'bb']
    grid = list(product(range(2), range(3)))    # different domain per slot
    assert grid == [(0, 0), (0, 1), (0, 2), (1, 0), (1, 1), (1, 2)]

    multisets = list(combinations_with_replacement(a, k))  # C(n+k-1,k)
    assert multisets == [(10, 10), (10, 20), (10, 30),
                         (20, 20), (20, 30), (30, 30)]
    subsets = [s for k in range(len(a) + 1) for s in combinations(a, k)]
    assert len(subsets) == 8 and subsets[0] == ()
    assert list(mask_subsets(a))[3] == [10, 20]
    assert list(submasks(0b1010)) == [0b1010, 0b1000, 0b0010, 0]
    assert brute([-1, 0, 1], 0) == 4
    assert knapsack([(2, 5), (3, 7), (4, 8)], 5) == 12
    assert assignment([[9, 2], [3, 8]]) == 5
    assert colorings(3, [(0, 1), (1, 2)], 2) == 2
    assert coin_ways([1, 2, 3], 2, 4) == 2
    tree = [[1], [0, 2], [1]]
    assert set(tree_paths(tree)) == {(0,), (1,), (2,), (0, 1), (1, 2), (0, 1, 2)}
    assert list(simple_paths(tree, 0, 2)) == [(0, 1, 2)]
    assert list(partitions([1, 2])) == [((1, 2),), ((1,), (2,))]
    assert tsp([[None, 2, 5], [2, None, 3], [5, 3, None]]) == 10
    assert mst(3, [(0, 1, 2), (1, 2, 3), (0, 2, 5)]) == 5


# All index subsets, including empty. O(n*2**n) time, O(n) extra space.
# Duplicate values are separate choices; iterate instead of storing all subsets.
def mask_subsets(a):
    for mask in range(1 << len(a)):
        yield [a[i] for i in range(len(a)) if mask >> i & 1]


# All submasks, descending, INCLUDING zero. O(2**popcount(mask)), O(1) space.
# mask must be nonnegative; stop at zero or (s-1)&mask cycles forever.
def submasks(mask):
    assert mask >= 0
    s = mask
    while True:
        yield s
        if s == 0:
            break
        s = (s - 1) & mask


# Count index subsets summing to target, INCLUDING empty; negatives are OK.
# O(n*2**n) time, O(n) extra space. Do not prune sum > target with negatives.
def brute(a, target):
    answer = 0
    for k in range(len(a) + 1):
        for chosen in combinations(a, k):
            if sum(chosen) == target:
                answer += 1
    return answer


# 0/1 knapsack: each (weight,value) used at most once; empty is allowed.
# O(n*2**n) time, O(n) space. Nonnegative weights and capacity required.
def knapsack(items, capacity):
    best = 0
    for take in product((0, 1), repeat=len(items)):
        weight = sum(w for (w, v), yes in zip(items, take) if yes)
        value = sum(v for (w, v), yes in zip(items, take) if yes)
        if weight <= capacity:
            best = max(best, value)
    return best


# Minimum assignment: cost[worker][job], square n*n matrix, all jobs distinct.
# O(n*n!) time, O(n) extra space. Empty assignment costs 0; negatives are OK.
def assignment(cost):
    n = len(cost)
    return min(sum(cost[i][p[i]] for i in range(n))
               for p in permutations(range(n)))


# Count proper colorings with q LABELED colors; edges use 0-based vertices.
# O(q**n * (n+m+1)) time, O(n+q) space. Self-loop => 0; empty graph => 1.
# Require n,q >= 0. Repeated edges are harmless; color names are NOT identified.
def colorings(n, edges, q):
    answer = 0
    for color in product(range(q), repeat=n):
        if all(color[u] != color[v] for u, v in edges):
            answer += 1
    return answer


# Count unordered ways to choose exactly k coins summing to target, with reuse.
# Enumeration: O((k+1)*C(d+k-1,k)) time, O(d+k) space for d distinct coins (d>0).
# Preprocessing: expected O(len(coins) + d*log(d)) time to deduplicate/sort.
# k >= 0. Deduplicate denominations; (1,2) and (2,1) are the same way.
def coin_ways(coins, k, target):
    coins = sorted(set(coins))
    return sum(sum(chosen) == target
               for chosen in combinations_with_replacement(coins, k))


# Every simple path in an UNDIRECTED TREE (also works for a forest).
# adj has both directions, no loops/parallel edges/cycles; vertices are 0-based.
# Yield vertex tuples, including singletons; reverse paths counted only once.
# O(n**2 + total output length) time, O(n) space; O(n**3) time on a chain.
# Tiny trees only: recursive DFS uses O(n) Python call depth.
def tree_paths(adj):
    path = []

    def dfs(u, parent, start):
        path.append(u)
        if start <= u:
            yield tuple(path)
        for v in adj[u]:
            if v != parent:
                yield from dfs(v, u, start)
        path.pop()

    for start in range(len(adj)):
        yield from dfs(start, -1, start)


# All simple source->target paths in a directed or undirected graph.
# No repeated vertices; source==target yields only (source,), not cycles.
# Unique neighbors per adjacency list; valid endpoints required.
# O(n*n!) worst-case time, O(n) space on simple graphs; tiny n only.
# Backtrack visited state: a global 'visited forever' would miss paths.
def simple_paths(adj, source, target):
    used = [False] * len(adj)
    path = []

    def dfs(u):
        used[u] = True
        path.append(u)
        if u == target:
            yield tuple(path)
        else:
            for v in adj[u]:
                if not used[v]:
                    yield from dfs(v)
        path.pop()
        used[u] = False

    yield from dfs(source)


# Split a sequence into every possible list of nonempty CONTIGUOUS blocks.
# O(n*2**(n-1)) time, O(n) space for n>=1; empty input has one partition ().
# Cuts are between positions, not values; useful for checking partition DP.
def partitions(a):
    n = len(a)
    if n == 0:
        yield ()
        return
    for mask in range(1 << (n - 1)):
        blocks, start = [], 0
        for end in range(1, n + 1):
            if end == n or mask >> (end - 1) & 1:
                blocks.append(tuple(a[start:end]))
                start = end
        yield tuple(blocks)


# Cheapest tour from vertex 0, visiting every other vertex once, back to 0.
# Square cost matrix: None means missing edge; directed/negative costs OK.
# O(n*(n-1)!) time, O(n) space. Return None if impossible; n<=1 costs 0.
# Fixing the start removes rotations. A 2-vertex tour traverses both directions.
def tsp(cost):
    n = len(cost)
    if n <= 1:
        return 0
    best = None
    for order in permutations(range(1, n)):
        tour = (0,) + order + (0,)
        weights = [cost[u][v] for u, v in zip(tour, tour[1:])]
        if all(w is not None for w in weights):
            value = sum(weights)
            best = value if best is None else min(best, value)
    return best


# Minimum spanning tree by choosing n-1 edges and checking connectivity.
# Undirected edge list (u,v,w); loops, parallel edges, negative weights OK.
# O(m + n*C(m,n-1)) time, O(m+n) space for n>=1; tiny m only.
# Connected + exactly n-1 edges implies a tree. None if disconnected; n=0 => 0.
def mst(n, edges):
    if n == 0:
        return 0
    best = None
    for chosen in combinations(edges, n - 1):
        adj = [[] for _ in range(n)]
        for u, v, w in chosen:
            adj[u].append(v)
            adj[v].append(u)
        seen, stack = {0}, [0]
        while stack:
            for v in adj[stack.pop()]:
                if v not in seen:
                    seen.add(v)
                    stack.append(v)
        if len(seen) == n:
            value = sum(w for u, v, w in chosen)
            best = value if best is None else min(best, value)
    return best


# Default oracle input: n target, then n integers; output: subset count.
# EDIT input/check and stress.py's gen() together; Python integers don't overflow.
# python3 stress.py './fast' 'python3 brute.py' 100
if __name__ == '__main__':
    import sys
    if sys.argv[1:] == ['--examples']:
        examples()
        print('OK')
    else:
        n, target, *a = map(int, sys.stdin.buffer.read().split())
        assert len(a) == n
        print(brute(a, target))
