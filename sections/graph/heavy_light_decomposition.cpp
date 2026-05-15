using vi = vector<int>;
#ifndef sz
#define sz(x) (int)(x).size()
#endif
#ifndef all
#define all(x) begin(x), end(x)
#endif

// Dependency used by HLD below: range add, range max, half-open [l, r).
struct Node {
    int lo, hi, lazy = 0, val = 0;
    Node *l = 0, *r = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {}
    void push() {
        if (hi - lo <= 1) return;
        int mid = (lo + hi) / 2;
        if (!l) l = new Node(lo, mid), r = new Node(mid, hi);
        if (lazy) {
            l->add(lo, hi, lazy);
            r->add(lo, hi, lazy);
            lazy = 0;
        }
    }
    void add(int L, int R, int x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            val += x;
            lazy += x;
            return;
        }
        push();
        l->add(L, R, x);
        r->add(L, R, x);
        val = max(l->val, r->val);
    }
    int query(int L, int R) {
        if (R <= lo || hi <= L) return INT_MIN;
        if (L <= lo && hi <= R) return val;
        push();
        return max(l->query(L, R), r->query(L, R));
    }
};

// 0-indexed. VALS_EDGES=true stores edge values at the deeper endpoint.
// Path/subtree operations are O(log^2 N) with the Node above.
template <bool VALS_EDGES> struct HLD {
    int N, tim = 0;
    vector<vi> adj;
    vi par, siz, rt, pos;
    Node *tree;
    HLD(vector<vi> adj_)
        : N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1),
          rt(N), pos(N), tree(new Node(0, N)) { dfsSz(0); dfsHld(0); }
    void dfsSz(int v) {
        if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
        for (int& u : adj[v]) {
            par[u] = v;
            dfsSz(u);
            siz[v] += siz[u];
            if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
        }
    }
    void dfsHld(int v) {
        pos[v] = tim++;
        for (int u : adj[v]) {
            rt[u] = (u == adj[v][0] ? rt[v] : u);
            dfsHld(u);
        }
    }
    template <class B> void process(int u, int v, B op) {
        for (; rt[u] != rt[v]; v = par[rt[v]]) {
            if (pos[rt[u]] > pos[rt[v]]) swap(u, v);
            op(pos[rt[v]], pos[v] + 1);
        }
        if (pos[u] > pos[v]) swap(u, v);
        op(pos[u] + VALS_EDGES, pos[v] + 1);
    }
    void modifyPath(int u, int v, int val) {
        process(u, v, [&](int l, int r) { tree->add(l, r, val); });
    }
    int queryPath(int u, int v) {
        int res = INT_MIN;
        process(u, v, [&](int l, int r) { res = max(res, tree->query(l, r)); });
        return res;
    }
    void modifySubtree(int v, int val) {
        tree->add(pos[v] + VALS_EDGES, pos[v] + siz[v], val);
    }
    int querySubtree(int v) {
        return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
    }
};
//  op(pos[u] + VALS_EDGES, pos[v] + 1);
//   - HLD<false>: values are on vertices.
//       - Path u..v includes both endpoints.
//       - Query/update range starts at pos[u].
//   - HLD<true>: values are on edges.
//       - Store each edge’s value at the deeper child vertex.
//       - Path u..v should exclude the LCA vertex, because no edge is stored “on” the LCA.
//       - So range starts at pos[u] + 1.
//   Example: edge values on path 2 -> 1 -> 3.
//   The LCA is 1. The edges are represented at vertices 2 and 3, not at 1, so VALS_EDGES=true skips pos[1].