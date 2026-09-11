// Heuristic subset-sum DECISION for nonnegative weights/target.
// true proves reachable; false means NOT FOUND (clipping may lose solutions).
// Time O(trials*n*ceil((2W+1)/64)), memory O(W/64+n), with packed bitsets.
// States are signed corrections in [-W,W]. Weights/target fit signed 64-bit.
// Usage: windowSubset({4,7,9}, 11, 20, 10, rng). No witness reconstruction.
#include "common.hpp"

bool windowSubset(const vector<ll>& a, ll target, int W,
                 int trials, mt19937_64& rng) {
    assert(target >= 0 && W >= 0 && W <= (INT_MAX-1)/2 && trials >= 0);
    if (!target) return true;
    vector<ll> delta; ll base = 0;
    for (ll x : a) {
        assert(x >= 0);
        if (x <= target-base) { base += x; delta.push_back(-x); }
        else delta.push_back(x);
    }
    ll goal = target-base;
    if (!goal) return true;
    if (goal > W) return false;
    int size = 2*W+1;
    while (trials--) {
        shuffle(delta.begin(), delta.end(), rng);
        int words = (size+63LL)/64;
        vector<ull> dp(words); dp[W/64] = 1ULL << (W%64);
        for (ll x : delta) {
            if (x > 2LL*W || x < -2LL*W) continue;
            int q = abs(x)/64, b = abs(x)%64;
            if (x > 0) {
                for (int i = words-1; i >= q; --i) {
                    ull v = dp[i-q] << b;
                    if (b && i > q) v |= dp[i-q-1] >> (64-b);
                    dp[i] |= v;
                }
            } else if (x < 0) {
                for (int i = 0; i+q < words; ++i) {
                    ull v = dp[i+q] >> b;
                    if (b && i+q+1 < words) v |= dp[i+q+1] << (64-b);
                    dp[i] |= v;
                }
            }
            if (size%64) dp.back() &= (1ULL << (size%64))-1;
        }
        int at = W+(int)goal;
        if (dp[at/64] >> (at%64) & 1) return true;
    }
    return false;
}
