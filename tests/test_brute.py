"""Run: python3 tests/test_brute.py -- recipes, edge cases, exhaustive oracle check."""
import importlib.util
import random
import subprocess
import sys
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PATH = ROOT / "sections/misc/brute.py"
spec = importlib.util.spec_from_file_location("brute", PATH)
mod = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mod)


def test_recipes():
    mod.examples()
    for values in ([], [1], [1, 1]):
        for fn in (mod.combinations, mod.permutations,
                   mod.combinations_with_replacement):
            assert list(fn(values, 0)) == [()]
        assert list(mod.product(values, repeat=0)) == [()]
        for fn in (mod.combinations, mod.permutations):
            assert list(fn(values, len(values) + 1)) == []
    assert list(mod.product([], repeat=2)) == []
    assert list(mod.combinations_with_replacement([], 2)) == []
    assert list(mod.combinations([1, 1], 1)) == [(1,), (1,)]
    assert list(mod.permutations([1, 1])) == [(1, 1), (1, 1)]
    assert list(mod.combinations_with_replacement([7], 3)) == [(7, 7, 7)]
    for fn in (mod.combinations, mod.permutations,
               mod.combinations_with_replacement):
        try:
            list(fn([1], -1))
        except ValueError:
            pass
        else:
            raise AssertionError("negative selection size must fail")
    for n in range(7):
        a = list(range(n))
        expected = {s for k in range(n + 1) for s in mod.combinations(a, k)}
        got = list(mod.mask_subsets(a))
        assert len(got) == 2**n
        assert {tuple(s) for s in got} == expected
    assert list(mod.mask_subsets([1, 1])) == [[], [1], [1], [1, 1]]
    for mask in range(128):
        assert list(mod.submasks(mask)) == [s for s in range(mask, -1, -1)
                                          if s & mask == s]


def test_oracle():
    # Independent include/exclude recursion counts equal-valued positions separately.
    def sums(a):
        if not a:
            return [0]
        tail = sums(a[1:])
        return tail + [a[0] + x for x in tail]

    for n in range(6):
        for a in mod.product([-1, 0, 1], repeat=n):
            expected = Counter(sums(a))
            for target in range(-n - 1, n + 2):
                assert mod.brute(a, target) == expected[target], (a, target)
    assert mod.brute([10**30, -10**30], 0) == 2
    for inp, want in (("0 0\n", "1"), ("3 0\n-1 0 1\n", "4"),
                      ("3 2\n1 1 1\n", "3")):
        result = subprocess.run([sys.executable, str(PATH)], input=inp,
                                capture_output=True, text=True, check=True)
        assert result.stdout.strip() == want


def test_optimization():
    rng = random.Random(17)

    def pack(items, capacity):
        if not items:
            return 0
        (w, v), *rest = items
        best = pack(rest, capacity)
        return max(best, v + pack(rest, capacity - w)) if w <= capacity else best

    def assign(cost, used=()):
        i = len(used)
        if i == len(cost):
            return 0
        return min(cost[i][j] + assign(cost, used + (j,))
                   for j in range(len(cost)) if j not in used)

    for n in range(7):
        for _ in range(10):
            items = [(rng.randrange(4), rng.randrange(-3, 7)) for _ in range(n)]
            capacity = rng.randrange(8)
            assert mod.knapsack(items, capacity) == pack(items, capacity)
            cost = [[rng.randrange(-5, 6) for _ in range(n)] for _ in range(n)]
            assert mod.assignment(cost) == assign(cost)
    assert mod.knapsack([(0, 5), (0, -1), (2, 7)], 0) == 5


def test_counting():
    # Recursive coloring checks conflicts as vertices are added.
    def paint(n, edges, q, colors=()):
        if any(u < len(colors) and v < len(colors) and colors[u] == colors[v]
               for u, v in edges):
            return 0
        if len(colors) == n:
            return 1
        return sum(paint(n, edges, q, colors + (c,)) for c in range(q))

    for n in range(5):
        possible = list(mod.combinations(range(n), 2))
        for edges in mod.mask_subsets(possible):
            for q in range(4):
                assert mod.colorings(n, edges, q) == paint(n, edges, q)
    assert mod.colorings(1, [(0, 0)], 3) == 0
    assert mod.colorings(2, [(0, 1), (0, 1)], 3) == 6

    # Independent recursion picks a quantity per denomination.
    def coins_count(coins, k, target):
        if not coins:
            return int(k == 0 and target == 0)
        return sum(coins_count(coins[1:], k - count, target - count * coins[0])
                   for count in range(k + 1))

    for coins in ([], [1], [1, 1, 2], [0, 1, 3], [-1, 0, 2]):
        for k in range(5):
            for target in range(-5, 13):
                assert mod.coin_ways(coins, k, target) == coins_count(
                    sorted(set(coins)), k, target)


def test_tree_paths():
    rng = random.Random(29)
    assert list(mod.tree_paths([])) == []
    for n in range(1, 10):
        trees = [[(i - 1, i) for i in range(1, n)],
                 [(0, i) for i in range(1, n)]]  # chain and star
        trees += [[(rng.randrange(i), i) for i in range(1, n)] for _ in range(20)]
        for edges in trees:
            labels = list(range(n))
            rng.shuffle(labels)
            adj = [[] for _ in range(n)]
            for u, v in edges:
                u, v = labels[u], labels[v]
                adj[u].append(v)
                adj[v].append(u)
            # Independent BFS parent reconstruction for every endpoint pair.
            expected = set()
            for start in range(n):
                parent, queue = {start: -1}, [start]
                for u in queue:
                    for v in adj[u]:
                        if v not in parent:
                            parent[v] = u
                            queue.append(v)
                for end in range(start, n):
                    path, u = [], end
                    while u != -1:
                        path.append(u)
                        u = parent[u]
                    expected.add(tuple(reversed(path)))
            got = list(mod.tree_paths(adj))
            assert len(got) == n * (n + 1) // 2
            assert set(got) == expected
            assert list(mod.tree_paths(adj)) == got  # reset on repeated calls
    assert set(mod.tree_paths([[1], [0], []])) == {(0,), (1,), (2,), (0, 1)}


def test_graph_paths():
    # Exhaust all directed 3-vertex graphs, including cycles and self-loops.
    n = 3
    for mask in range(1 << (n * n)):
        adj = [[v for v in range(n) if mask >> (u * n + v) & 1] for u in range(n)]
        for source in range(n):
            for target in range(n):
                expected = {(source,)} if source == target else set()
                if source != target:
                    middle = [v for v in range(n) if v not in (source, target)]
                    for k in range(len(middle) + 1):
                        for p in mod.permutations(middle, k):
                            path = (source,) + p + (target,)
                            if all(v in adj[u] for u, v in zip(path, path[1:])):
                                expected.add(path)
                got = list(mod.simple_paths(adj, source, target))
                assert len(got) == len(set(got))
                assert set(got) == expected
    # Many branches sharing the same vertex exercise visited-state backtracking.
    adj = [[v for v in range(5) if v != u] for u in range(5)]
    assert len(list(mod.simple_paths(adj, 0, 4))) == 16


def test_partitions():
    def split(a):
        if not a:
            return [()]
        return [(tuple(a[:i]),) + rest for i in range(1, len(a) + 1)
                for rest in split(a[i:])]

    for n in range(8):
        for a in (list(range(n)), [0] * n):
            got = list(mod.partitions(a))
            assert len(got) == (2**(n - 1) if n else 1)
            assert set(got) == set(split(a))


def test_tsp_and_mst():
    rng = random.Random(31)

    def tour(cost, u=0, used=frozenset({0})):
        if len(cost) <= 1:
            return 0
        if len(used) == len(cost):
            return cost[u][0]
        choices = []
        for v in range(len(cost)):
            if v not in used and cost[u][v] is not None:
                rest = tour(cost, v, used | {v})
                if rest is not None:
                    choices.append(cost[u][v] + rest)
        return min(choices, default=None)

    def kruskal(n, edges):
        parent = list(range(n))
        def find(u):
            while parent[u] != u:
                u = parent[u]
            return u
        total, taken = 0, 0
        for u, v, w in sorted(edges, key=lambda e: e[2]):
            u, v = find(u), find(v)
            if u != v:
                parent[u] = v
                total += w
                taken += 1
        return total if taken == max(0, n - 1) else None

    for n in range(7):
        for _ in range(25):
            cost = [[rng.choice([None, -5, 0, 2, 7]) for _ in range(n)]
                    for _ in range(n)]
            assert mod.tsp(cost) == tour(cost)
            edges = [(rng.randrange(n), rng.randrange(n), rng.randrange(-5, 8))
                     for _ in range(rng.randrange(10))] if n else []
            assert mod.mst(n, edges) == kruskal(n, edges)
    assert mod.tsp([[None, 10**30], [-1, None]]) == 10**30 - 1
    assert mod.tsp([[None, 1], [None, None]]) is None
    assert mod.mst(2, [(0, 0, -100), (0, 1, 5), (0, 1, -2)]) == -2
    assert mod.mst(3, [(0, 1, 1)]) is None
    assert mod.mst(1, [(0, 0, -5)]) == 0


if __name__ == "__main__":
    test_recipes()
    test_oracle()
    test_optimization()
    test_counting()
    test_tree_paths()
    test_graph_paths()
    test_partitions()
    test_tsp_and_mst()
    print("all Python brute-force tests passed")
