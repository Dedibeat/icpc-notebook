// Solve x^k = a (mod p) for prime p, via primitive root + BSGS index log.
// Requires NT_essentials.cpp (modpow, inv_any) and primitive_root.cpp.
// Complexity: O(sqrt(p) log p). Returns sorted distinct roots; a=0 gives {0}.
// Usage: vector<long long> xs = kth_roots_mod_prime(a, k, p);
long long discrete_log_prime_root(long long g, long long a, long long p) {
    // g must be a primitive root modulo prime p, and a != 0.
    long long m = (long long)sqrtl(p - 1) + 1;
    unordered_map<long long, long long> baby;
    long long cur = 1;
    for (long long j = 0; j < m; j++) {
        if (!baby.count(cur)) baby[cur] = j;
        cur = (__int128)cur * g % p;
    }
    long long step = modpow(modpow(g, m, p), p - 2, p);
    cur = a % p;
    for (long long i = 0; i <= m; i++) {
        auto it = baby.find(cur);
        if (it != baby.end()) return i * m + it->second;
        cur = (__int128)cur * step % p;
    }
    return -1;
}

vector<long long> kth_roots_mod_prime(long long a, long long k, long long p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return {0};
    if (p == 2) return {1};

    long long g = generator(p);
    long long ind = discrete_log_prime_root(g, a, p); // a = g^ind
    if (ind == -1) return {};

    long long mod = p - 1, d = __gcd(k, mod);
    if (ind % d) return {};

    long long kk = ((k / d) % (mod / d) + (mod / d)) % (mod / d);
    long long b = ind / d, md = mod / d;
    long long y0 = (__int128)b * inv_any(kk, md) % md;

    vector<long long> ans;
    for (long long t = 0; t < d; t++) ans.push_back(modpow(g, y0 + t * md, p));
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    return ans;
}
