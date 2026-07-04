// Discrete log: smallest x >= 0 with a^x = b (mod m), or -1 if none.
// Works for ANY a, b, m >= 1 (no coprimality/primality needed).
// O(sqrt(m)) time and memory. Requires chash from misc/custom_hash.cpp
// (identity-hash unordered_map can be degraded to O(m) by chosen m).
// Source: cp-algorithms extended BSGS.
long long discrete_log(long long a, long long b, long long m) {
    a %= m; b %= m;
    if (a < 0) a += m;
    if (b < 0) b += m;
    long long k = 1 % m, add = 0, g;
    while ((g = __gcd(a, m)) > 1) {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g; m /= g; add++;
        k = (__int128)k * (a / g) % m;
    }
    // now gcd(a, m) = 1: find a^(n*p) * k = b * a^q
    long long n = (long long)sqrtl(m) + 1;
    unordered_map<long long, long long, chash> vals;
    long long cur = b;
    for (long long q = 0; q <= n; q++) {
        vals[cur] = q; // keep the LARGEST q per value -> smallest answer
        cur = (__int128)cur * a % m;
    }
    long long an = 1;
    for (long long i = 0; i < n; i++) an = (__int128)an * a % m;
    cur = k;
    for (long long p = 1; p <= n; p++) {
        cur = (__int128)cur * an % m;
        auto it = vals.find(cur);
        if (it != vals.end()) return n * p - it->second + add;
    }
    return -1;
}
