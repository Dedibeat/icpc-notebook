// Evaluate degree < n polynomial from arbitrary samples y[i]=f(x[i]) mod HMOD.
// Time O(n^2 + n log HMOD), memory O(n) for normalized input copies.
// x coordinates must be distinct modulo HMOD; prime is fixed at 1000000007.
// Returns nullopt for empty/mismatched input or repeated x residues (even equal y).
// Usage: lagrangeGeneral({-1,2,4}, {1,4,16}, 3).value() == 9.
#include "common.hpp"

optional<ll> lagrangeGeneral(vector<ll> x, vector<ll> y, ll at) {
    if (x.empty() || x.size() != y.size()) return nullopt;
    int n = x.size(); at = hnorm(at);
    for (ll& v : x) v = hnorm(v);
    for (ll& v : y) v = hnorm(v);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll num = y[i], den = 1;
        for (int j = 0; j < n; ++j) if (j != i) {
            if (x[i] == x[j]) return nullopt;
            num = num * hnorm(at-x[j]) % HMOD;
            den = den * hnorm(x[i]-x[j]) % HMOD;
        }
        ans = (ans + num*hpow(den, HMOD-2)) % HMOD;
    }
    return ans;
}
