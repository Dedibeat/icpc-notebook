#include <bits/stdc++.h>
using namespace std;

#include "../sections/math/hadamard_transform.cpp"

int main() {
    vector<long long> a = {1, 2, 3, 4};
    vector<long long> b = {5, 6, 7, 8};
    vector<long long> got = xor_convolution(a, b);
    vector<long long> want(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            want[i ^ j] += a[i] * b[j];
    assert(got == want);

    vector<long long> c = {3, -1, 4, 2};
    auto orig = c;
    fwht(c);
    fwht(c, true);
    assert(c == orig);
}
