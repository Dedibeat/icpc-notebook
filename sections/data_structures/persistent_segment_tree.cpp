// Persistent point add and range sum. Start with Node root{} on [0,n-1].
// Keep the root returned by each update. All bounds are inclusive.
// Update/query O(log n), with O(log n) new nodes per update.
struct Node {
    // ---- customize for the operation ----
    using V = long long;
    static constexpr V VID = 0;
    static V merge(V a, V b) { return a + b; }
    static V apply(V a, V x) { return a + x; } // use x for assignment

    V val = VID;
    Node *lc = 0, *rc = 0;
    static V get(Node *v) { return v ? v->val : VID; }

    Node* update(int l, int r, int p, V x) {
        Node *v = new Node(*this);
        if (l == r) {
            v->val = apply(val, x);
            return v;
        }
        int m = l + (r - l) / 2;
        Node empty, *&c = p <= m ? v->lc : v->rc;
        c = (c ? c : &empty)->update(
            p <= m ? l : m + 1, p <= m ? m : r, p, x);
        v->val = merge(get(v->lc), get(v->rc));
        return v;
    }

    V query(int l, int r, int L, int R) {
        if (r < L || R < l) return VID;
        if (L <= l && r <= R) return val;
        int m = l + (r - l) / 2;
        return merge(lc ? lc->query(l, m, L, R) : VID,
                     rc ? rc->query(m + 1, r, L, R) : VID);
    }
};
