#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/zeta_and_mobius.cpp"

int main() {
    mt19937 rng(31337);

    // subset zeta: F(S) = sum over subsets T of S; mobius inverts
    for (int it = 0; it < 20; it++) {
        int b = 1 + rng() % 4, n = 1 << b;
        vector<long long> f(n);
        for (auto& x : f) x = (long long)(rng() % 200) - 100;
        vector<long long> F = f;
        subsetZeta(F);
        for (int s = 0; s < n; s++) {
            long long sum = 0;
            for (int t = s;; t = (t - 1) & s) {
                sum += f[t];
                if (t == 0) break;
            }
            assert(F[s] == sum);
        }
        subsetMobius(F);
        assert(F == f);
    }

    // superset zeta: F(S) = sum over supersets of S; mobius inverts
    for (int it = 0; it < 20; it++) {
        int b = 1 + rng() % 4, n = 1 << b;
        vector<long long> f(n);
        for (auto& x : f) x = (long long)(rng() % 200) - 100;
        vector<long long> F = f;
        supersetZeta(F);
        for (int s = 0; s < n; s++) {
            long long sum = 0;
            for (int t = 0; t < n; t++) if ((t & s) == s) sum += f[t];
            assert(F[s] == sum);
        }
        supersetMobius(F);
        assert(F == f);
    }

    // divisor zeta: F(i) = sum_{d | i} f(d); mobius inverts
    for (int it = 0; it < 20; it++) {
        int n = 1 + rng() % 60;
        vector<long long> f(n + 1);
        for (int i = 1; i <= n; i++) f[i] = (long long)(rng() % 200) - 100;
        vector<long long> F = f;
        divisorZeta(F);
        for (int i = 1; i <= n; i++) {
            long long sum = 0;
            for (int d = 1; d <= i; d++) if (i % d == 0) sum += f[d];
            assert(F[i] == sum);
        }
        divisorMobius(F);
        assert(F == f);
    }

    // multiple zeta: F(i) = sum_{i | m, m <= n} f(m); mobius inverts
    for (int it = 0; it < 20; it++) {
        int n = 1 + rng() % 60;
        vector<long long> f(n + 1);
        for (int i = 1; i <= n; i++) f[i] = (long long)(rng() % 200) - 100;
        vector<long long> F = f;
        multipleZeta(F);
        for (int i = 1; i <= n; i++) {
            long long sum = 0;
            for (int m = i; m <= n; m += i) sum += f[m];
            assert(F[i] == sum);
        }
        multipleMobius(F);
        assert(F == f);
    }
    return 0;
}
