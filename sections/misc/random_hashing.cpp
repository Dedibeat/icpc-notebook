// Set-equality hashing: hash of a set = xor of random keys of its elements.
// Requires: mt19937_64 rng (rand_mt19937_faster.cpp). Compare multisets with
// sums instead of xor (xor cancels duplicate pairs).
uint64_t rnd() {
    return rng();
}
unordered_map<int, uint64_t> h;
uint64_t getHash(int x) {
    if (!h.count(x)) h[x] = rnd();
    return h[x];
}
cur ^= getHash(x); // toggle x
