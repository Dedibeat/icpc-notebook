#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/mod_inverse_table.cpp"

long long slow_pow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    build_inv(0);
    assert(fact.size() == 1 && fact[0] == 1 && ifact[0] == 1);

    build_inv(20);
    assert(invv[1] == 1);
    for (int i = 1; i <= 20; i++) {
        assert(invv[i] == slow_pow(i, MOD - 2));
        assert(fact[i] * ifact[i] % MOD == 1);
    }

    assert(C(5, 2) == 10);
    assert(C(20, 0) == 1);
    assert(C(20, 20) == 1);
    assert(C(20, -1) == 0);
    assert(C(20, 21) == 0);
    assert(C(20, 10) == 184756);
}
