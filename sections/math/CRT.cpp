// Solve x = a1 (mod m1), x = a2 (mod m2); returns {x, lcm(m1,m2)} with
// 0 <= x < lcm, or {-1,-1} if impossible. Chain calls for >2 congruences.
// O(log max(m1,m2)). Requires egcd, positive moduli and lcm fitting long long.
pair<long long,long long> crt(long long a1, long long m1,
                              long long a2, long long m2) {
    long long x, y;
    long long g = egcd(m1, m2, x, y);

    __int128 diff = (__int128)a2 - a1;
    if (diff % g != 0) return {-1, -1};

    long long lcm = m1 / g * m2;
    __int128 t = diff / g * x;
    t %= m2 / g;

    long long ans = (a1 + (__int128)m1 * t) % lcm;
    if (ans < 0) ans += lcm;

    return {ans, lcm};
}
