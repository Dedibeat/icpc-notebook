#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/discrete_mod.cpp"

vector<long long> brute(long long a, long long k, long long p) {
    a %= p;
    if (a < 0) a += p;
    vector<long long> ans;
    for (long long x = 0; x < p; x++)
        if (mod_pow(x, k, p) == a) ans.push_back(x);
    return ans;
}

int main() {
    assert(kth_roots_mod_prime(0, 5, 17) == vector<long long>{0});
    assert(kth_roots_mod_prime(1, 1, 2) == vector<long long>{1});

    assert(kth_roots_mod_prime(4, 2, 7) == (vector<long long>{2, 5}));
    assert(kth_roots_mod_prime(3, 2, 7).empty());
    assert(kth_roots_mod_prime(1, 3, 7) == (vector<long long>{1, 2, 4}));

    for (long long p : {3, 5, 7, 11, 17, 31, 101}) {
        for (long long k = 1; k <= 20; k++) {
            for (long long a = 0; a < p; a++) {
                auto got = kth_roots_mod_prime(a, k, p);
                auto want = brute(a, k, p);
                assert(got == want);
            }
        }
    }

    long long p = 1000003;
    auto xs = kth_roots_mod_prime(123456, 17, p);
    for (long long x : xs) assert(mod_pow(x, 17, p) == 123456);
}
