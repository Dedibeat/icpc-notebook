// Set-equality hashing: hash of a set = xor of random keys of its elements.
// Requires: mt19937_64 rng64 (rand_mt19937_faster.cpp). Compare multisets with
// sums instead of xor (xor cancels duplicate pairs).
// Expected O(1) per lookup. Collisions are possible.
unordered_map<int, uint64_t> h;
uint64_t getHash(int x) {
    if (!h.count(x)) h[x] = rng64();
    return h[x];
}
// Usage: cur ^= getHash(x); // toggle x
