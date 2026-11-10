#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/k_smallest_subset_sums.cpp"

int main() {
    using Sums = vector<__int128>;
    assert(k_smallest_subset_sums({}, 0).empty());
    assert(k_smallest_subset_sums({}, 3) == Sums{0});
    assert(k_smallest_subset_sums({1, 6, 3, -3}, 9) ==
           (Sums{-3, -2, 0, 0, 1, 1, 3, 3, 4}));
    assert(k_smallest_subset_sums({0, 0, 0}, 10) == Sums(8, 0));
    assert(k_smallest_subset_sums({LLONG_MIN, LLONG_MIN, LLONG_MAX, LLONG_MAX}, 4) ==
           (Sums{2 * (__int128)LLONG_MIN, (__int128)LLONG_MIN - 1,
                 (__int128)LLONG_MIN - 1, LLONG_MIN}));
    assert(k_smallest_subset_sums({LLONG_MAX, LLONG_MAX}, 4).back() ==
           2 * (__int128)LLONG_MAX);

    mt19937 rng(3108);
    for (int it = 0; it < 1000; ++it) {
        int n = rng() % 13;
        vector<long long> a(n);
        for (auto& x : a) x = (int)(rng() % 21) - 10;
        Sums want;
        for (int mask = 0; mask < (1 << n); ++mask) {
            __int128 sum = 0;
            for (int i = 0; i < n; ++i)
                if (mask >> i & 1) sum += a[i];
            want.push_back(sum);
        }
        sort(want.begin(), want.end());
        assert(k_smallest_subset_sums(a, (1 << n) + 1) == want);
        int k = rng() % (want.size() + 1);
        want.resize(k);
        assert(k_smallest_subset_sums(a, k) == want);
    }

    const int n = 200000;
    Sums want(n, -5LL * n + 5);
    want[0] -= 5;
    assert(k_smallest_subset_sums(vector<long long>(n, -5), n) == want);
}
