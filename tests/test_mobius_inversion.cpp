#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/mobius_inversion.cpp"

int main() {
    mobius_sieve(20);
    vector<int> want = {0, 1, -1, -1, 0, -1, 1, -1, 0, 0, 1,
                        -1, 0, -1, 1, 1, 0, -1, 0, -1, 0};
    for (int i = 1; i <= 20; i++) assert(mu[i] == want[i]);

    mobius_sieve(10);
    for (int i = 1; i <= 10; i++) assert(mu[i] == want[i]);
    assert(pcnt == 4);
}
