// Precompute modular inverses and factorial inverses modulo prime MOD.
// Complexity: O(n). Use when 0 <= n < MOD.
// Pitfalls: inv[i] uses inv[MOD % i], not inv[i-1]; MOD must be prime.
// Usage: build_inv(1000000); then invv[i], fact[i], ifact[i], C(n,k).
const long long MOD = 1000000007;
vector<long long> invv, fact, ifact;

void build_inv(int n) {
    invv.assign(n + 1, 0);
    fact.assign(n + 1, 1);
    ifact.assign(n + 1, 1);
    if (n >= 1) invv[1] = 1;
    for (int i = 2; i <= n; i++)
        invv[i] = MOD - (MOD / i) * invv[MOD % i] % MOD;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        ifact[i] = ifact[i - 1] * invv[i] % MOD; // this one uses previous value
    }
}

long long C(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}
