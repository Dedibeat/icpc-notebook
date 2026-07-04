// Factorials/inverses mod prime, auto-extending. C(n,k) is O(1) after extend.
using ll = long long;
const ll mod = 1e9 + 7; // EDIT: prime modulus
struct Binom {
    vector<ll> fact{1}, inv{1}, invfact{1};

    void extend(ll n) {
        ll cur = fact.size() - 1;
        if (cur >= n) return;

        fact.resize(n + 1);
        inv.resize(n + 1);
        invfact.resize(n + 1);

        for (ll i = cur + 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % mod;

            if (i == 1) inv[i] = 1;
            else inv[i] = mod - mod / i * inv[mod % i] % mod;

            invfact[i] = invfact[i - 1] * inv[i] % mod;
        }
    }

    ll C(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        extend(n);
        return fact[n] * invfact[k] % mod * invfact[n - k] % mod;
    }
} binom;
