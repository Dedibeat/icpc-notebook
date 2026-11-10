// Kuhn max bipartite matching, left size n / right size m. O(V*E) worst case
// but fast in practice with the repeat loop. add(l,r) adds an edge;
// matching() returns (left,right) pairs; match[r] = left partner of r or -1.
// Large/adversarial graphs: use Dinic (dinic_2.cpp) with unit capacities
// source->left->right->sink: O(E sqrt V), same as Hopcroft-Karp.
// Konig: min vertex cover size = max matching; complement = max independent set.
// Example: edges (0,1),(1,0) produce two pairs (order unspecified).
struct bipartite {
    int n, m;
    vector<vector<int>> g;
    vector<int> match;
    vector<bool> visited;
    bipartite(int n, int m) : n(n), m(m), g(n), match(m, -1) {}
    void add(int a, int b) { g[a].push_back(b); }
    bool kuhn(int at) {
        if (visited[at]) return false;
        visited[at] = true;
        for (int to : g[at])
            if (match[to] == -1 || kuhn(match[to])) { match[to] = at; return true; }
        return false;
    }
    vector<pair<int, int>> matching() {
        fill(match.begin(), match.end(), -1);
        vector<bool> paired(n);
        for (bool repeat = true; repeat;) {
            repeat = false;
            visited.assign(n, false);
            for (int i = 0; i < n; i++)
                if (!paired[i] && kuhn(i)) paired[i] = repeat = true;
        }
        vector<pair<int, int>> ans;
        for (int r = 0; r < m; r++) if (match[r] != -1) ans.emplace_back(match[r], r);
        return ans;
    }
};

// Dense variant (e.g. n=m=5000, ~n^2/2 edges): rows are bitsets, right ids < DK_MAXR.
// O(n*(n+m)*DK_MAXR/64) worst case; memory n*DK_MAXR/8 bytes. Recursion depth <= n.
// Tries a free neighbor first; keeps seen marks across FAILED searches (still dead).
// adj[l][r]=1 adds edge l-r; solve() returns the size; mt[r] = left partner or -1.
// Pitfall: keep the AND in member tmp; a bitset temporary per frame overflows stack.
const int DK_MAXR = 5000;
struct DenseKuhn {
    vector<bitset<DK_MAXR>> adj;
    bitset<DK_MAXR> unseen, freeR, tmp;
    vector<int> mt;
    DenseKuhn(int n) : adj(n), mt(DK_MAXR, -1) {}
    int first(int at, const bitset<DK_MAXR>& b) { tmp = adj[at]; tmp &= b; return tmp._Find_first(); }
    bool dfs(int at) {
        int to = first(at, freeR);
        if (to < DK_MAXR) { freeR[to] = 0; mt[to] = at; return true; }
        while ((to = first(at, unseen)) < DK_MAXR) { // to is matched
            unseen[to] = 0;
            if (dfs(mt[to])) { mt[to] = at; return true; }
        }
        return false;
    }
    int solve() {
        fill(mt.begin(), mt.end(), -1);
        freeR.set(), unseen.set();
        int res = 0;
        for (int i = 0; i < (int)adj.size(); i++) if (dfs(i)) res++, unseen.set();
        return res;
    }
};
