#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/fft_v2.cpp"
#include "../sections/math/fft_mod.cpp"

int main() {
    vector<long long> a = {1000000006LL, 2, 3};
    vector<long long> b = {4, 5, 6};
    auto got = convMod<1000000007>(a, b);
    vector<long long> want(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            want[i + j] = (want[i + j] + a[i] * b[j]) % 1000000007;
    assert(got == want);
}
