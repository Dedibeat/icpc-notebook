#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/meet_in_the_middle.cpp"

int main() {
    mt19937 rng(6);
    for (int n = 0; n <= 20; ++n) for (int it = 0; it < 30; ++it) {
        vector<long long> a(n);
        for (auto& x : a) x = (int)(rng()%21)-10;
        long long lim = (int)(rng()%41)-20, want = LLONG_MIN;
        for (int mask = 0; mask < (1<<n); ++mask) {
            long long s = 0;
            for (int i = 0; i < n; ++i) if (mask>>i&1) s += a[i];
            if (s <= lim) want = max(want, s);
        }
        assert(max_subset_sum_leq(a, lim) == want);
    }
}
