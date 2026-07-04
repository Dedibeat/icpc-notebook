#include <bits/stdc++.h>
using namespace std;

#include "../sections/misc/custom_hash.cpp"

int main() {
    // correctness vs std::map on random ops
    mt19937_64 rng(4242);
    unordered_map<long long, int, chash> um;
    map<long long, int> bm;
    for (int it = 0; it < 100000; it++) {
        long long k = (long long)(rng() % 1000) - 500;
        int op = rng() % 3;
        if (op == 0) {
            int v = (int)(rng() % 1000);
            um[k] = v;
            bm[k] = v;
        } else if (op == 1) {
            um.erase(k);
            bm.erase(k);
        } else {
            auto iu = um.find(k);
            auto ib = bm.find(k);
            assert((iu == um.end()) == (ib == bm.end()));
            if (ib != bm.end()) assert(iu->second == ib->second);
        }
    }
    assert(um.size() == bm.size());

    // adversarial pattern for the identity hash: keys sharing residue mod a
    // libstdc++ bucket prime must still hash to spread buckets
    unordered_map<long long, int, chash> adv;
    const long long P = 107897; // gcc bucket prime
    for (long long i = 0; i < 20000; i++) adv[i * P] = 1;
    size_t worst = 0;
    for (size_t b = 0; b < adv.bucket_count(); b++)
        worst = max(worst, adv.bucket_size(b));
    assert(worst < 50); // identity hash would put ~all in one bucket
    return 0;
}
