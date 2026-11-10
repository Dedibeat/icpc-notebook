// egcd for a,b >= 0: g = gcd(a,b), a*x+b*y = g. O(log max(a,b)).
// inv_any: inverse mod positive mod (or -1). inv: prime mod, a nonzero mod mod.
// modpow: nonnegative exponent, positive modulus. O(log e) time.
long long egcd(long long a, long long b, long long& x, long long& y) {
    if (!b) { x = 1, y = 0; return a; }
    long long g = egcd(b, a % b, y, x); // note swapped x, y
    y -= a / b * x;
    return g;
}

long long inv_any(long long a, long long mod) {
    a %= mod;
    if (a < 0) a += mod;
    long long x, y;
    long long g = egcd(a, mod, x, y);
    if (g != 1) return -1; // no inverse
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

long long modpow(long long a, long long e, long long mod) {
    a %= mod;
    if (a < 0) a += mod;
    long long r = 1 % mod;
    while (e) {
        if (e & 1) r = (__int128)r * a % mod;
        a = (__int128)a * a % mod;
        e >>= 1;
    }
    return r;
}

long long inv(long long a, long long mod) {
    return modpow(a, mod - 2, mod);
}
