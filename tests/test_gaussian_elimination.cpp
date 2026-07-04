#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/Gaussian_elimination.cpp"

int main() {
    mt19937 rng(808);
    const long long p = 5;
    for (int it = 0; it < 500; it++) {
        int n = 1 + rng() % 4, m = 1 + rng() % 4;
        vector<vector<long long>> a(n, vector<long long>(m + 1));
        for (auto& r : a) for (auto& x : r) x = (long long)(rng() % 11) - 5; // negatives too

        // brute force: enumerate all p^m assignments
        long long count = 0, total = 1;
        for (int i = 0; i < m; i++) total *= p;
        vector<long long> x(m);
        for (long long mask = 0; mask < total; mask++) {
            long long t = mask;
            for (int i = 0; i < m; i++) { x[i] = t % p; t /= p; }
            bool ok = true;
            for (int i = 0; i < n && ok; i++) {
                long long s = 0;
                for (int j = 0; j < m; j++) s += a[i][j] * x[j];
                ok = ((s - a[i][m]) % p + p) % p == 0;
            }
            if (ok) count++;
        }

        vector<long long> sol;
        int free_vars = gauss(a, p, sol);
        if (count == 0) {
            assert(free_vars == -1);
        } else {
            assert(free_vars >= 0);
            long long expect = 1;
            for (int i = 0; i < free_vars; i++) expect *= p;
            assert(count == expect); // # solutions = p^free
            for (int i = 0; i < n; i++) { // returned sol satisfies the system
                long long s = 0;
                for (int j = 0; j < m; j++) s += a[i][j] * sol[j];
                assert(((s - a[i][m]) % p + p) % p == 0);
            }
        }
    }
    // larger prime sanity: unique 3x3 system, verify residuals
    const long long P = 1000000007;
    vector<vector<long long>> A = {{2, 1, 1, 7}, {1, 3, 2, 13}, {1, 0, 0, 2}};
    vector<long long> sol;
    assert(gauss(A, P, sol) == 0);
    for (auto& r : A) {
        long long s = 0;
        for (int j = 0; j < 3; j++) s = (s + r[j] * sol[j]) % P;
        assert(s == r[3] % P);
    }
    assert(sol[0] == 2); // x fixed by third equation
    return 0;
}
