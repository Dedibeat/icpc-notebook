#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/ntt.cpp"

int main() {
    mt19937_64 rng(42);
    for (int it = 0; it < 50; it++) {
        int n = 1 + (int)(rng() % 40), m = 1 + (int)(rng() % 40);
        vector<ll> a(n), b(m);
        for (auto& x : a) x = rng() % NTT_MOD;
        for (auto& x : b) x = rng() % NTT_MOD;
        vector<ll> naive(n + m - 1, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                naive[i + j] = (naive[i + j] + (__int128)a[i] * b[j]) % NTT_MOD;
        assert(conv_ntt(a, b) == naive);
    }
    // edge cases
    assert(conv_ntt({}, {1, 2}).empty());
    assert((conv_ntt({3}, {5}) == vector<ll>{15}));
    // size exactly a power of two
    vector<ll> ones(8, 1);
    auto c = conv_ntt(ones, ones);
    assert((int)c.size() == 15 && c[7] == 8 && c[0] == 1 && c[14] == 1);
    return 0;
}
