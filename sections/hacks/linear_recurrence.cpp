// Infer recurrence mod HMOD, then evaluate its N-th term (0-indexed).
// Time: BM O(s^2 + s log HMOD); evaluation O(L^2 log N). Space O(s+L).
// Need a proven order bound L and >=2L samples; prefix fits alone prove nothing.
// Empty recurrence means zero sequence. initial must contain >=rec.size() terms.
// Usage: nthTerm({0,1}, {1,1}, 10) == 55.
#include "common.hpp"

vector<ll> berlekampMassey(vector<ll> s) {
    for (ll& x : s) x = hnorm(x);
    vector<ll> C{1}, B{1};
    int L = 0, shift = 1; ll last = 1;
    for (int i = 0; i < (int)s.size(); ++i) {
        ll d = s[i];
        for (int j = 1; j <= L; ++j)
            d = (d + C[j] * s[i-j]) % HMOD;
        if (!d) { ++shift; continue; }
        auto old = C;
        ll coef = d * hpow(last, HMOD-2) % HMOD;
        C.resize(max(C.size(), B.size()+shift), 0);
        for (int j = 0; j < (int)B.size(); ++j)
            C[j+shift] = hnorm(C[j+shift] - coef*B[j]%HMOD);
        if (2*L <= i) {
            L = i+1-L; B = old; last = d; shift = 1;
        } else ++shift;
    }
    C.resize(L+1); C.erase(C.begin());
    for (ll& x : C) x = hnorm(-x);
    return C; // s[i] = sum rec[j] * s[i-1-j]
}
ll nthTerm(vector<ll> initial, vector<ll> rec, ull N) {
    int L = rec.size(); assert(initial.size() >= rec.size());
    for (ll& x : initial) x = hnorm(x);
    for (ll& x : rec) x = hnorm(x);
    if (N < initial.size()) return initial[N];
    if (!L) return 0;
    auto mul = [&](vector<ll> a, vector<ll> b) {
        vector<ll> c(2*L-1);
        for (int i = 0; i < L; ++i)
            for (int j = 0; j < L; ++j)
                c[i+j] = (c[i+j] + a[i]*b[j]) % HMOD;
        for (int i = 2*L-2; i >= L; --i)
            for (int j = 1; j <= L; ++j)
                c[i-j] = (c[i-j] + c[i]*rec[j-1]) % HMOD;
        c.resize(L); return c;
    };
    vector<ll> ans(L), x(L); ans[0] = 1;
    if (L == 1) x[0] = rec[0]; else x[1] = 1;
    for (; N; N >>= 1, x = mul(x, x))
        if (N & 1) ans = mul(ans, x);
    ll value = 0;
    for (int i = 0; i < L; ++i)
        value = (value + ans[i]*initial[i]) % HMOD;
    return value;
}
