// Range chmin (a[i] = min(a[i], v)) and range sum/max on [l,r).
// O((n+q) log n) total for q operations, O(n) memory.
// Only cap a whole node when second < v < mx. Equality needs descent.
// Keep LLONG_MIN reserved and all segment sums within long long.
// Example: Beats b({5,2,5}); b.chmin(0,3,3); b.sum(0,3)==8.
struct Beats {
    using ll = long long;
    struct Node {
        ll sum = 0, mx = LLONG_MIN, second = LLONG_MIN;
        int cnt = 0;
    };
    int n;
    vector<Node> t;
    Beats(const vector<ll>& a) : n(a.size()), t(4*n) {
        if (n) build(1, 0, n, a);
    }
    Node merge(Node a, Node b) {
        if (a.mx < b.mx) swap(a,b);
        a.sum += b.sum;
        if (a.mx == b.mx) {
            a.cnt += b.cnt;
            a.second = std::max(a.second, b.second);
        } else a.second = std::max(a.second, b.mx);
        return a;
    }
    void build(int p, int l, int r, const vector<ll>& a) {
        if (r-l == 1) {
            t[p] = {a[l], a[l], LLONG_MIN, 1};
            return;
        }
        int m = (l+r)/2;
        build(2*p, l, m, a);
        build(2*p+1, m, r, a);
        t[p] = merge(t[2*p], t[2*p+1]);
    }
    void cap(int p, ll v) {
        auto& a = t[p];
        if (a.mx <= v) return;
        a.sum = a.sum + ((__int128)v - a.mx) * a.cnt;
        a.mx = v;
    }
    void push(int p) {
        cap(2*p, t[p].mx);
        cap(2*p+1, t[p].mx);
    }
    void chmin(int p, int l, int r, int ql, int qr, ll v) {
        if (qr <= l || r <= ql || t[p].mx <= v) return;
        if (ql <= l && r <= qr && t[p].second < v) {
            cap(p,v);
            return;
        }
        push(p);
        int m = (l+r)/2;
        chmin(2*p, l, m, ql, qr, v);
        chmin(2*p+1, m, r, ql, qr, v);
        t[p] = merge(t[2*p], t[2*p+1]);
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return {};
        if (ql <= l && r <= qr) return t[p];
        push(p);
        int m = (l+r)/2;
        return merge(query(2*p,l,m,ql,qr), query(2*p+1,m,r,ql,qr));
    }
    void chmin(int l, int r, ll v) { if (l < r) chmin(1,0,n,l,r,v); }
    ll sum(int l, int r) { return l < r ? query(1,0,n,l,r).sum : 0; }
    ll max(int l, int r) { return l < r ? query(1,0,n,l,r).mx : LLONG_MIN; }
};
