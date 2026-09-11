"""Black-box tests of the user's complete solution, including multi-case resets."""
import heapq
import itertools
import random
import subprocess
import sys

MOD = 998244353


def prufer_tree(n, sequence):
    degree = [1] * n
    for v in sequence:
        degree[v] += 1
    leaves = [v for v in range(n) if degree[v] == 1]
    heapq.heapify(leaves)
    edges = []
    for v in sequence:
        u = heapq.heappop(leaves)
        edges.append((u, v))
        degree[v] -= 1
        if degree[v] == 1:
            heapq.heappush(leaves, v)
    edges.append(tuple(leaves))
    return edges


def brute(n, edges):
    adj = [[] for _ in range(n)]
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
    answer = 0
    for mask in range(1, 1 << n):
        vertices = [v for v in range(n) if mask >> v & 1]
        size = len(vertices)
        # An induced subgraph of a tree is a forest: size-1 edges means connected.
        if sum(bool(mask >> u & 1 and mask >> v & 1) for u, v in edges) != size-1:
            continue
        centroids = 0
        for removed in vertices:
            unseen = set(vertices) - {removed}
            largest = 0
            while unseen:
                stack = [unseen.pop()]
                count = 0
                while stack:
                    v = stack.pop()
                    count += 1
                    for u in adj[v]:
                        if u in unseen:
                            unseen.remove(u)
                            stack.append(u)
                largest = max(largest, count)
            centroids += 2*largest <= size
        assert centroids in (1, 2)
        answer += centroids == 1
    return answer % MOD


def main(binary):
    rng = random.Random(20260911)
    cases = [(1, [], 1)]
    for n in range(2, 6):
        for sequence in itertools.product(range(n), repeat=n-2):
            edges = prufer_tree(n, sequence)
            cases.append((n, edges, brute(n, edges)))
    for _ in range(100):
        n = rng.randint(2, 10)
        edges = prufer_tree(n, [rng.randrange(n) for _ in range(n-2)])
        cases.append((n, edges, brute(n, edges)))
    rng.shuffle(cases)
    # A path subset is an interval, with one centroid iff its size is odd.
    # A star has 2^(n-1)+(n-1) connected subsets; only its edges have two centroids.
    for n in (3000, 1, 3000, 2, 50, 3):
        path = [(i-1, i) for i in range(1, n)]
        cases.append((n, path, sum(n-k+1 for k in range(1, n+1, 2)) % MOD))
        star = [(0, i) for i in range(1, n)]
        cases.append((n, star, pow(2, n-1, MOD)))
    lines = [str(len(cases))]
    for n, edges, _ in cases:
        lines.append(str(n))
        lines.extend(f"{u+1} {v+1}" for u, v in edges)
    result = subprocess.run([binary], input="\n".join(lines)+"\n", text=True,
                            capture_output=True, check=True, timeout=120)
    actual = [int(x) for x in result.stdout.split()]
    assert len(actual) == len(cases), (len(actual), len(cases))
    for i, (got, (n, edges, expected)) in enumerate(zip(actual, cases)):
        assert got == expected, (i, n, edges, got, expected)
    print(f"Unique-centroid subsets: {len(cases)} cases passed, including n=3000 and resets")


if __name__ == "__main__":
    main(sys.argv[1])
