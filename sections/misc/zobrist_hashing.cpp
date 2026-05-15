// Zobrist hashing: xor random keys for incremental state hashes.
// Source: standard Zobrist/tabulation hashing.
// Complexity: build O(positions * values), update/query O(1).
// Pitfalls: probabilistic collisions; state values must be in range.
// Usage: h ^= key[pos][old]; h ^= key[pos][now];
struct Zobrist {
    vector<vector<uint64_t>> key;

    Zobrist(int positions, int values, uint64_t seed = chrono::steady_clock::now().time_since_epoch().count()) {
        mt19937_64 rng(seed);
        key.assign(positions, vector<uint64_t>(values));
        for (auto& row : key)
            for (uint64_t& x : row) x = rng();
    }

    uint64_t hash(const vector<int>& state) const {
        uint64_t h = 0;
        for (int i = 0; i < (int)state.size(); i++)
            if (state[i] >= 0) h ^= key[i][state[i]];
        return h;
    }
};
