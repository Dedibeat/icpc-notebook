#include <bits/stdc++.h>
using namespace std;
#define I long

struct f {
    I m = 0, c = -4e18;
    I e(I x) {
        return m*x + c;
    }
};

struct T {
    I n; vector<f> st;
    T(I n = 0) : n(n), st(4*n) {}

    void a(I i, I l, I r, f fn) {
        I m = l + (r-l) / 2;
        if (fn.e(m) > st[i].e(m)) swap(fn, st[i]);

        if (l+1 == r) return;
        if (fn.e(l) > st[i].e(l)) a(2*i+1,l,m,fn);
        else if (fn.e(r-1) > st[i].e(r-1)) a(2*i+2,m,r,fn);
    }

    void s(I i, I l, I r, I ql, I qr, f fn) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {a(i, l, r, fn); return;}
        I m = l + (r-l) / 2;
        s(2*i+1,l,m,ql,qr,fn); s(2*i+2,m,r,ql,qr,fn);
    }

    I q(I i, I l, I r, I k) {
        if (l+1 == r) return st[i].e(k);

        I m = l + (r-l) / 2;
        if (k < m) return max(st[i].e(k), q(2*i+1,l,m,k));
        else return max(st[i].e(k), q(2*i+2,m,r,k));
    }

    void a(f fn, I l, I r) {
        s(0, 0, n, l, r+1, fn);
    }

    I q(I x) {
        return q(0, 0, n, x);
    }
};

using pi = pair<I, I>;
main() {
    I n, k; cin >> n >> k;
    vector<I> x(n); for (I i = 0; i < n; i++) cin >> x[i];

    vector<I> P(n, -1), N(n, n), y, Q, R;
    for (I i = 0; i < n; i++) {
        while (!Q.empty() && x[i] < x[Q.back()]) {
            N[Q.back()] = i;
            Q.pop_back();
        }
        Q.push_back(i);
    }
    for (I i = n-1; i >= 0; i--) {
        while (!R.empty() && x[i] < x[R.back()]) {
            P[R.back()] = i;
            R.pop_back();
        }
        R.push_back(i);
    }

    auto t = T(n+5);

    for (I i = 0; i < n; i++) {
        I L = P[i]+1, R = N[i] - 1;
        I b = R - k + 1;
        I p = min(L, b);
        I q = max(L, b);

        t.a(f{x[i], x[i] * (k-L)}, L-k+1, p);
        t.a(f{0, x[i] * min(k, R - L+1)}, p, q);
        t.a(f{-x[i], x[i] * (R + 1)}, q, R);

        I a = t.q(i-k+1);
        if (i >= k-1) y.push_back(a);
    }

    for (auto x : y) cout << x << " "; cout << "\n";
}