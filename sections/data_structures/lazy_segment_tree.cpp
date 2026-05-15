// Range assignment + range sum. 0-indexed, inclusive query/update bounds.
// Change apply/pull/neutral to adapt to other operations.
// Time: O(log N) per operation.
struct segTree {
    int n;
    vector<long long> sum, lazy;
    vector<bool> has_lazy;

    segTree(int nn = 0) { init(nn); }

    void init(int nn) {
        n = nn;
        sum.assign(4 * max(1, n), 0);
        lazy.assign(4 * max(1, n), 0);
        has_lazy.assign(4 * max(1, n), false);
    }

    void build(const vector<long long>& a, int node, int l, int r) {
        if (l == r) {
            sum[node] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(a, node << 1, l, m);
        build(a, node << 1 | 1, m + 1, r);
        sum[node] = sum[node << 1] + sum[node << 1 | 1];
    }

    void apply(int node, int l, int r, long long v) {
        sum[node] = (r - l + 1) * v;
        lazy[node] = v;
        has_lazy[node] = true;
    }

    void push(int node, int l, int r) {
        if (!has_lazy[node] || l == r) return;
        int m = (l + r) >> 1;
        apply(node << 1, l, m, lazy[node]);
        apply(node << 1 | 1, m + 1, r, lazy[node]);
        has_lazy[node] = false;
    }

    void assign_range(int node, int tl, int tr, int l, int r, long long v) {
        if (l > r) return;
        if (tl == l && tr == r) {
            apply(node, tl, tr, v);
            return;
        }
        push(node, tl, tr);
        int tm = (tl + tr) >> 1;
        assign_range(node << 1, tl, tm, l, min(r, tm), v);
        assign_range(node << 1 | 1, tm + 1, tr, max(l, tm + 1), r, v);
        sum[node] = sum[node << 1] + sum[node << 1 | 1];
    }

    long long range_query(int node, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (tl == l && tr == r) return sum[node];
        push(node, tl, tr);
        int tm = (tl + tr) >> 1;
        return range_query(node << 1, tl, tm, l, min(r, tm)) +
               range_query(node << 1 | 1, tm + 1, tr, max(l, tm + 1), r);
    }

    long long point_query(int node, int tl, int tr, int pos) {
        if (tl == tr) return sum[node];
        push(node, tl, tr);
        int tm = (tl + tr) >> 1;
        if (pos <= tm) return point_query(node << 1, tl, tm, pos);
        return point_query(node << 1 | 1, tm + 1, tr, pos);
    }
};
