#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/matrix_power.cpp"

int main() {
    // Fibonacci
    long long f0 = 0, f1 = 1;
    for (int n = 0; n <= 40; n++) {
        Mat R = mpow({{1, 1}, {1, 0}}, n);
        assert(R[0][1] == f0 % MMOD);
        long long t = (f0 + f1) % MMOD;
        f0 = f1; f1 = t;
    }
    // identity for e = 0
    Mat I = mpow({{5, 7}, {11, 13}}, 0);
    assert(I[0][0] == 1 && I[0][1] == 0 && I[1][0] == 0 && I[1][1] == 1);
    // non-square multiply
    Mat v = mul({{1, 2, 3}}, {{1}, {10}, {100}});
    assert((int)v.size() == 1 && (int)v[0].size() == 1 && v[0][0] == 321);
    // big exponent sanity: A^(2^40) via repeated squaring equals mpow
    Mat A = {{2, 1}, {1, 1}};
    Mat B = A;
    for (int i = 0; i < 40; i++) B = mul(B, B);
    assert(mpow(A, 1LL << 40) == B);
    return 0;
}
