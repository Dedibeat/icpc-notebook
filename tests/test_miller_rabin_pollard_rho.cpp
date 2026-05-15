#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/miller_rabin_pollard_rho.cpp"

int main() {
    vector<ull> primes = {2, 3, 5, 97, 1000000007ULL, 2305843009213693951ULL};
    for (ull p : primes) assert(isPrime(p));

    vector<ull> composites = {0, 1, 4, 9, 221, 341, 561, 1000000007ULL * 1000000009ULL};
    for (ull x : composites) assert(!isPrime(x));

    assert(factor(1).empty());

    auto check = [](ull n, vector<ull> want) {
        vector<ull> got = factor(n);
        sort(got.begin(), got.end());
        sort(want.begin(), want.end());
        assert(got == want);
        ull prod = 1;
        for (ull x : got) {
            assert(isPrime(x));
            prod *= x;
        }
        assert(prod == n);
    };

    check(2, {2});
    check(12, {2, 2, 3});
    check(59049, {3, 3, 3, 3, 3, 3, 3, 3, 3, 3});
    check(1000000007ULL * 1000000009ULL, {1000000007ULL, 1000000009ULL});
    check(2305843009213693951ULL, {2305843009213693951ULL});

    for (ull n = 0; n <= 5000; n++) {
        bool brute = n >= 2;
        for (ull d = 2; d * d <= n; d++) if (n % d == 0) brute = false;
        assert(isPrime(n) == brute);
    }
    for (ull n = 1; n <= 2000; n++) {
        vector<ull> got = factor(n);
        ull prod = 1;
        for (ull x : got) {
            assert(isPrime(x));
            prod *= x;
        }
        assert(prod == n);
    }
}
