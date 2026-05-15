// Deterministic Miller-Rabin and Pollard Rho factorization for unsigned 64-bit.
// Source: KACTL MillerRabin/Factor, using __int128 mod multiplication.
// Complexity: primality O(7 log n); factorization expected about O(n^(1/4)).
// Pitfalls: call factor(n) only for n >= 1; returns unsorted prime factors; factor(1) is empty.
// Usage: isPrime(n); auto f = factor(n); sort(f.begin(), f.end());
using ull = unsigned long long;
using u128 = __uint128_t;

ull mod_mul(ull a, ull b, ull mod) {
    return (ull)((u128)a * b % mod);
}

ull mod_pow(ull a, ull e, ull mod) {
    ull r = 1;
    while (e) {
        if (e & 1) r = mod_mul(r, a, mod);
        a = mod_mul(a, a, mod);
        e >>= 1;
    }
    return r;
}

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull d = n - 1, s = 0;
    while ((d & 1) == 0) d >>= 1, s++;
    for (ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        ull x = mod_pow(a % n, d, n), i = s;
        while (x != 1 && x != n - 1 && a % n && i--) x = mod_mul(x, x, n);
        if (x != n - 1 && i != s) return false;
    }
    return true;
}

ull pollard(ull n) {
    if (n % 2 == 0) return 2;
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (true) {
        ull c = uniform_int_distribution<ull>(1, n - 1)(rng);
        ull x = uniform_int_distribution<ull>(0, n - 1)(rng), y = x, d = 1;
        auto f = [&](ull v) { return (mod_mul(v, v, n) + c) % n; };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            ull diff = x > y ? x - y : y - x;
            d = gcd(diff, n);
        }
        if (d != n) return d;
    }
}

vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ull d = pollard(n);
    auto a = factor(d), b = factor(n / d);
    a.insert(a.end(), b.begin(), b.end());
    return a;
}
