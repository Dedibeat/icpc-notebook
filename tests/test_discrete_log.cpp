#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/discrete_log.cpp"

long long bruteLog(long long a, long long b, long long m, long long bound) {
    long long cur = 1 % m;
    for (long long x = 0; x <= bound; x++) {
        if (cur == b % m) return x;
        cur = cur * a % m;
    }
    return -1;
}

int main() {
    // exhaustive small: all a, b, m up to 30 (covers non-coprime, a=0, b=1...)
    for (long long m = 1; m <= 30; m++)
        for (long long a = 0; a < m; a++)
            for (long long b = 0; b < m; b++) {
                // trajectory of a^x mod m cycles within m steps; 3m is safe
                long long want = bruteLog(a, b, m, 3 * m + 5);
                long long got = discrete_log(a, b, m);
                assert(got == want);
            }
    // random larger moduli
    mt19937_64 rng(777);
    for (int it = 0; it < 2000; it++) {
        long long m = 2 + rng() % 100000;
        long long a = rng() % m, b = rng() % m;
        long long got = discrete_log(a, b, m);
        long long want = bruteLog(a, b, m, 2 * m + 5);
        assert(got == want);
    }
    // known values
    assert(discrete_log(2, 8, 1000000007) == 3);
    assert(discrete_log(3, 1, 998244353) == 0);
    assert(discrete_log(5, 33, 58) == 9);
    return 0;
}
