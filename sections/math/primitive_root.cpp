// Smallest primitive root modulo PRIME p (factors phi = p-1).
// Requires modpow from NT_essentials.cpp. O(sqrt p + ans * log^2 p).
// For NTT: root of mod 998244353 is 3. Used by discrete_mod.cpp.
long long generator(long long p) {
    if (p == 2) return 1;
    vector<long long> fact;
    long long phi = p - 1, n = phi;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0) n /= i;
        }
    if (n > 1) fact.push_back(n);
    for (long long res = 2; res <= p; res++) {
        bool ok = true;
        for (long long f : fact)
            ok &= modpow(res, phi / f, p) != 1;
        if (ok) return res;
    }
    return -1;
}
