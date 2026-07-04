// Polynomial hash mod 2^64. get(l,r) hashes s[l..r) in O(1).
// Pitfalls: single hash; for paranoid problems build two Hash objects with
// different B (e.g. 1000003 and 998244353) and compare pairs.
struct Hash {
    static const uint64_t B = 1000003;
    vector<uint64_t> h, p;

    Hash(const string& s) {
        int n = s.size();
        h.assign(n + 1, 0);
        p.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = h[i] * B + (unsigned char)s[i] + 1;
            p[i + 1] = p[i] * B;
        }
    }

    // hash of s[l..r)
    uint64_t get(int l, int r) {
        return h[r] - h[l] * p[r - l];
    }
};
