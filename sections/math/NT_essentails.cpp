long long egcd(long long a, long long b, long long& x, long long& y) {
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    long long x1, y1;
    long long g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

long long inv_any(long long a, long long mod) {
    long long x, y;
    long long g = egcd(a, mod, x, y);
    if (g != 1) return -1; // no inverse
    x %= mod;
    if (x < 0) x += mod;
    return x;
}   

long long modpow(long long a, long long e, long long mod) {
    long long r = 1;
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

