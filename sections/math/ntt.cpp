// NTT convolution mod 998244353 (primitive root 3). Exact, no precision issues.
// conv_ntt(a,b)[k] = sum a[i]*b[k-i] mod p. O(n log n), sizes up to 2^23.
// Inputs must be in [0, mod). For arbitrary mod use fft_mod.cpp.
// Other NTT primes (root 3): 167772161, 469762049, 1004535809.
using ll = long long;
// EDIT ONLY this pair (mod, primitive root) together; max size = largest
// power of two dividing mod-1 (2^23 here) — update the assert below too.
const ll NTT_MOD = 998244353, NTT_G = 3;

ll ntt_pow(ll a, ll e) {
    ll r = 1;
    for (a %= NTT_MOD; e; e >>= 1, a = a * a % NTT_MOD)
        if (e & 1) r = r * a % NTT_MOD;
    return r;
}

void ntt(vector<ll>& a, bool inv) {
    int n = a.size(); // power of 2
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = ntt_pow(NTT_G, (NTT_MOD - 1) / len);
        if (inv) w = ntt_pow(w, NTT_MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll wn = 1;
            for (int j = 0; j < len / 2; j++, wn = wn * w % NTT_MOD) {
                ll u = a[i + j], v = a[i + j + len / 2] * wn % NTT_MOD;
                a[i + j] = (u + v) % NTT_MOD;
                a[i + j + len / 2] = (u - v + NTT_MOD) % NTT_MOD;
            }
        }
    }
    if (inv) {
        ll ninv = ntt_pow(n, NTT_MOD - 2);
        for (ll& x : a) x = x * ninv % NTT_MOD;
    }
}

vector<ll> conv_ntt(vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};
    int res = a.size() + b.size() - 1, n = 1;
    while (n < res) n <<= 1;
    assert(n <= (1 << 23)); // beyond 2^23 the roots silently break for this mod
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % NTT_MOD;
    ntt(a, true);
    a.resize(res);
    return a;
}
