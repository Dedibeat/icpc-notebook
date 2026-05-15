uint64_t rnd() {
    return rng();
}
unordered_map<int, uint64_t> h;
uint64_t getHash(int x) {
    if (!h.count(x)) h[x] = rnd();
    return h[x];
}
cur ^= getHash(x); // toggle x