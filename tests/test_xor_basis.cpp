#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/xor_basis.cpp"

int main() {
    // brute-force comparison on random small sets
    mt19937_64 rng(999);
    for (int it = 0; it < 200; it++) {
        int n = 1 + (int)(rng() % 8);
        vector<long long> v(n);
        for (auto& x : v) x = rng() % 1024;

        Basis b;
        for (long long x : v) b.add(x);

        set<long long> xors;
        for (int mask = 0; mask < (1 << n); mask++) {
            long long cur = 0;
            for (int i = 0; i < n; i++) if (mask >> i & 1) cur ^= v[i];
            xors.insert(cur);
        }
        long long mx = *xors.rbegin();
        assert(b.maxXor() == mx);
        assert((1LL << b.rank()) == (long long)xors.size());
        for (long long x : xors) assert(b.contains(x));
        for (int q = 0; q < 20; q++) {
            long long x = rng() % 1024;
            assert(b.contains(x) == (bool)xors.count(x));
        }
    }

    // high bits (near 2^60)
    Basis hb;
    hb.add(1LL << 59);
    hb.add((1LL << 59) | 1);
    assert(hb.rank() == 2);
    assert(hb.maxXor() == ((1LL << 59) | 1));

    // duplicates and zero
    Basis d;
    assert(!d.add(0));
    assert(d.add(5));
    assert(!d.add(5));
    assert(d.rank() == 1);
    return 0;
}
