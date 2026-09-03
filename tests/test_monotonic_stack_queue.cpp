#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/monotonic_stack_queue.cpp"

int main() {
    mt19937 rng(2);
    for (int n = 0; n <= 30; ++n) for (int it = 0; it < 50; ++it) {
        vector<long long> a(n);
        for (auto& x : a) x = rng() % 7;
        auto [l, r] = smaller_bounds(a);
        for (int i = 0; i < n; ++i) {
            int bl = -1, br = n;
            for (int j = i - 1; j >= 0; --j) if (a[j] < a[i]) { bl = j; break; }
            for (int j = i + 1; j < n; ++j) if (a[j] <= a[i]) { br = j; break; }
            assert(l[i] == bl && r[i] == br);
        }
        for (int k = 1; k <= n; ++k) {
            auto got = sliding_max(a, k);
            for (int i = 0; i + k <= n; ++i)
                assert(got[i] == *max_element(a.begin() + i, a.begin() + i + k));
        }
    }
    assert(sliding_max({1, 2}, 0).empty());
}
