// XOR linear basis over 64-bit values. add O(B), B = bits.
// rank() = basis size; number of DISTINCT subset xors = 2^rank
// (each achieved by exactly 2^(n-rank) subsets, empty subset gives 0).
// Pitfalls: reset (b = Basis()) between test cases; raise B for values >= 2^60.
// add inserts an independent vector and reports whether rank grew; contains
// tests representability; maxXor(start) maximizes start xor a subset xor.
// Example: add(3), add(5) => rank()==2, contains(6), maxXor()==6.
struct Basis {
    static const int B = 60;
    long long b[B] = {};
    bool add(long long x) { // false if x already representable
        for (int i = B - 1; i >= 0; i--) if (x >> i & 1) {
            if (!b[i]) { b[i] = x; return true; }
            x ^= b[i];
        }
        return false;
    }
    bool contains(long long x) {
        for (int i = B - 1; i >= 0; i--) if (x >> i & 1) x ^= b[i];
        return x == 0;
    }
    long long maxXor(long long start = 0) {
        long long r = start;
        for (int i = B - 1; i >= 0; i--) r = max(r, r ^ b[i]);
        return r;
    }
    int rank() {
        int r = 0;
        for (int i = 0; i < B; i++) r += b[i] != 0;
        return r;
    }
};
