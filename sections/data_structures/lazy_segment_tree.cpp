/**
 * ===================================================
 * USABILITY GUIDE
 * ===================================================
 * 1. Define Combine Operation:
 *    - Sum: combine(a,b) = a + b
 *    - Max: combine(a,b) = max(a,b)
 *    - Min: combine(a,b) = min(a,b)
 *    - Xor: combine(a,b) = a ^ b
 *
 * 2. Define Lazy Meaning:
 *    - Range Assignment: lazy[node] = v
 *    - Range Add: lazy[node] += v
 *    - Range Max-Update (chmax): lazy[node] = max(lazy[node], v)
 *
 * 3. Modify update_lazy():
 *    Example:
 *      - Range Assignment + Sum:
 *          val[node] = lazy[node];
 *          sum[node] = (r-l+1) * lazy[node];
 *
 *      - Range Add + Sum:
 *          val[node] += lazy[node];
 *          sum[node] += (r-l+1) * lazy[node];
 *
 *      - Range Assignment + Max:
 *          val[node] = lazy[node];
 *          sum[node] = lazy[node];  // here sum[] stores max
 *
 * 4. Adjust Query Neutral Value:
 *    - Sum: return 0
 *    - Max: return -INF
 *    - Min: return +INF
 *    - Xor: return 0
 *    - GCD: return 0
 *
 * Complexity: O(log N) per operation.
 * Root is at index 1, responsible for array[0..n-1].
 */
struct segTree {
    // NOTE: broken for assigning 0; lazy=0 means "no lazy". Use has_lazy[].
    int n;
    vector<int> val, sum, lazy;

    segTree(int nn) {
        n = nn;
        val.resize(n << 2);
        sum.resize(n << 2);
        lazy.resize(n << 2);
    }

    void build(vector<int>& a, int node, int l, int r) {
        if (l == r) {
            val[node] = a[l];
            sum[node] = a[l];   // adjust if using other ops
        } else {
            int m = (l + r) >> 1;
            build(a, node << 1, l, m);
            build(a, (node << 1) | 1, m + 1, r);
            val[node] = val[node << 1] + val[(node << 1) | 1]; // combine()
            sum[node] = sum[node << 1] + sum[(node << 1) | 1]; // combine()
        }
    }

    void update_lazy(int node, int l, int r) {
        if (!lazy[node]) return;
        int v = lazy[node];

        // Example: Range assignment with sum
        val[node] = v;
        sum[node] = (r - l + 1) * v;

        // For other ops: replace this block
    }

    void push(int node, int l, int r) {
        if (lazy[node]) {
            lazy[node << 1] = lazy[(node << 1) | 1] = lazy[node];
            update_lazy(node, l, r);

            int m = (l + r) >> 1;
            update_lazy(node << 1, l, m);
            update_lazy((node << 1) | 1, m + 1, r);
            lazy[node] = 0;
        }
    }

    void assign_range(int node, int tl, int tr, int l, int r, int v) {
        if (l > r) return;
        if (tl == l && tr == r) {
            lazy[node] = v;
            if (tl == tr) update_lazy(node, tl, tr);
            else push(node, tl, tr);
        } else {
            push(node, tl, tr);
            int tm = (tl + tr) >> 1;
            assign_range(node << 1, tl, tm, l, min(tm, r), v);
            assign_range((node << 1) | 1, tm + 1, tr, max(tm + 1, l), r, v);
            sum[node] = sum[node << 1] + sum[(node << 1) | 1]; // combine()
        }
    }

    int range_query(int node, int tl, int tr, int l, int r) {
        if (l > r) return 0;  // neutral element for sum
        if (tl == l && tr == r) {
            if (tl == tr) update_lazy(node, tl, tr);
            else push(node, tl, tr);
            return sum[node];
        }
        push(node, tl, tr);
        int tm = (tl + tr) >> 1;
        return range_query(node << 1, tl, tm, l, min(r, tm)) +
               range_query((node << 1) | 1, tm + 1, tr, max(tm + 1, l), r); // combine()
    }

    int point_query(int node, int tl, int tr, int pos) {
        if (tl > tr) return 0;
        if (tl == pos && tr == pos) {
            update_lazy(node, tl, tr);
            return val[node];
        }
        push(node, tl, tr);
        int tm = (tl + tr) >> 1;
        if (pos <= tm)
            return point_query(node << 1, tl, tm, pos);
        return point_query((node << 1) | 1, tm + 1, tr, pos);
    }
};
