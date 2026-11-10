// HLD: split paths and subtrees into half-open intervals on a 0-rooted tree.
// Build O(n) time/space; process(u,v,op) emits O(log n) intervals;
// subtree(v) gives one interval in O(1). pos[v] is the vertex's index.
// VALS_EDGES stores edges at their deeper endpoints and skips the LCA.
// Path intervals may be empty or arrive out of path order. DFS is recursive.
template <bool VALS_EDGES> struct HLD {
    int N, tim = 0;
    vector<vector<int>> adj;
    vector<int> par, siz, rt, pos;
    HLD(vector<vector<int>> adj_)
        : N(adj_.size()), adj(move(adj_)), par(N, -1), siz(N, 1), rt(N), pos(N) {
        if (N) { dfsSz(0); dfsHld(0); }
    }
    void dfsSz(int at) {
        if (par[at] != -1) adj[at].erase(find(adj[at].begin(), adj[at].end(), par[at]));
        for (int& to : adj[at]) {
            par[to] = at;
            dfsSz(to);
            siz[at] += siz[to];
            if (siz[to] > siz[adj[at][0]]) swap(to, adj[at][0]);
        }
    }
    void dfsHld(int at) {
        pos[at] = tim++;
        for (int to : adj[at]) {
            rt[to] = (to == adj[at][0] ? rt[at] : to);
            dfsHld(to);
        }
    }
    template <class B> void process(int u, int v, B op) { // op gets [l, r), may be empty
        for (; rt[u] != rt[v]; v = par[rt[v]]) {
            if (pos[rt[u]] > pos[rt[v]]) swap(u, v);
            op(pos[rt[v]], pos[v] + 1);
        }
        if (pos[u] > pos[v]) swap(u, v);
        op(pos[u] + VALS_EDGES, pos[v] + 1);
    }
    pair<int, int> subtree(int v) {
        return {pos[v] + VALS_EDGES, pos[v] + siz[v]};
    }
};
