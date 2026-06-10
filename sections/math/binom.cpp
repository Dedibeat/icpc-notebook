const int mod = 1e9 + 7;
struct Binom {
    vector<int> fact{1}, inv{1}, invfact{1};

    void extend(int n) {
        int cur = fact.size() - 1;
        if (cur >= n) return;

        fact.resize(n + 1);
        inv.resize(n + 1);
        invfact.resize(n + 1);

        for (int i = cur + 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % mod;

            if (i == 1) inv[i] = 1;
            else inv[i] = mod - mod / i * inv[mod % i] % mod;

            invfact[i] = invfact[i - 1] * inv[i] % mod;
        }
    }

    int C(int n, int k) {
        if (k < 0 || k > n) return 0;
        extend(n);
        return fact[n] * invfact[k] % mod * invfact[n - k] % mod;
    }
} binom;
