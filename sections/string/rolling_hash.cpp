// Polynomial rolling hash mod 2^61-1 with runtime-random base.
// get(l, r) hashes s[l..r) (HALF-OPEN) in O(1) after O(n) build.
// NEVER hash mod 2^64 via overflow: Thue-Morse strings of length 2048
// collide for EVERY base, and setters include such tests.
// All Hash objects share base HB, so hashes compare across strings.
// Collision prob per pair ~ n/2^61: single hash is fine at ICPC sizes.
const uint64_t HMOD = (1ULL << 61) - 1;
const uint64_t HB =
    mt19937_64(chrono::steady_clock::now().time_since_epoch().count())()
    % (HMOD - 300) + 257;

struct Hash {
    vector<uint64_t> h, p;

    static uint64_t mul(uint64_t a, uint64_t b) {
        __uint128_t c = (__uint128_t)a * b;
        uint64_t r = (uint64_t)(c >> 61) + ((uint64_t)c & HMOD);
        return r >= HMOD ? r - HMOD : r;
    }

    Hash(const string& s) {
        int n = s.size();
        h.assign(n + 1, 0);
        p.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = mul(h[i], HB) + (unsigned char)s[i] + 1;
            if (h[i + 1] >= HMOD) h[i + 1] -= HMOD;
            p[i + 1] = mul(p[i], HB);
        }
    }

    // hash of s[l..r)
    uint64_t get(int l, int r) {
        uint64_t x = h[r] + HMOD - mul(h[l], p[r - l]);
        return x >= HMOD ? x - HMOD : x;
    }
};
