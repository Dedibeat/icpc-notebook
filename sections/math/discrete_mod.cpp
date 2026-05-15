// Solve x^k = a (mod p) for prime p.
// Uses primitive root + baby-step giant-step discrete log.
// Complexity: O(sqrt(p) log p).
// Pitfalls: p must be prime; returns sorted distinct roots; a=0 returns {0}.
// Usage: vector<long long> xs = kth_roots_mod_prime(a, k, p);
__extension__ typedef __int128 i128;

long long mod_pow(long long a, long long e, long long mod) {
    long long r = 1 % mod;
    a %= mod;
    if (a < 0) a += mod;
    while (e) {
        if (e & 1) r = (i128)r * a % mod;
        a = (i128)a * a % mod;
        e >>= 1;
    }
    return r;
}

long long egcd(long long a, long long b, long long& x, long long& y) {
    if (!b) return x = 1, y = 0, a;
    long long x1, y1, g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

long long inv_mod(long long a, long long mod) {
    long long x, y, g = egcd(a, mod, x, y);
    if (g != 1) return -1;
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

long long primitive_root_prime(long long p) {
    if (p == 2) return 1;
    vector<long long> fac;
    long long n = p - 1;
    for (long long d = 2; d * d <= n; d++) if (n % d == 0) {
        fac.push_back(d);
        while (n % d == 0) n /= d;
    }
    if (n > 1) fac.push_back(n);
    for (long long g = 2; ; g++) {
        bool ok = true;
        for (long long q : fac) if (mod_pow(g, (p - 1) / q, p) == 1) {
            ok = false;
            break;
        }
        if (ok) return g;
    }
}

long long discrete_log_prime_root(long long g, long long a, long long p) {
    // g must be a primitive root modulo prime p, and a != 0.
    int m = (int)sqrt((long double)(p - 1)) + 1;
    unordered_map<long long, int> baby;
    long long cur = 1;
    for (int j = 0; j < m; j++) {
        if (!baby.count(cur)) baby[cur] = j;
        cur = (i128)cur * g % p;
    }
    long long step = mod_pow(mod_pow(g, m, p), p - 2, p);
    cur = a % p;
    for (int i = 0; i <= m; i++) {
        auto it = baby.find(cur);
        if (it != baby.end()) return 1LL * i * m + it->second;
        cur = (i128)cur * step % p;
    }
    return -1;
}

vector<long long> kth_roots_mod_prime(long long a, long long k, long long p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return {0};
    if (p == 2) return {1};

    long long g = primitive_root_prime(p);
    long long ind = discrete_log_prime_root(g, a, p); // a = g^ind
    if (ind == -1) return {};

    long long mod = p - 1, d = gcd(k, mod);
    if (ind % d) return {};

    long long kk = ((k / d) % (mod / d) + (mod / d)) % (mod / d);
    long long b = ind / d, md = mod / d;
    long long y0 = (i128)b * inv_mod(kk, md) % md;

    vector<long long> ans;
    for (long long t = 0; t < d; t++) ans.push_back(mod_pow(g, y0 + t * md, p));
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    return ans;
}
