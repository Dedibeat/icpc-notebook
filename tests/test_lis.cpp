#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/lis.cpp"

int main() {
    mt19937 rng(3);
    for (int n = 0; n <= 12; ++n) for (int it = 0; it < 100; ++it) {
        vector<long long> a(n);
        for (auto& x : a) x = (int)(rng() % 9) - 4;
        int best = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            long long last = LLONG_MIN; int len = 0; bool ok = true;
            for (int i = 0; i < n; ++i) if (mask >> i & 1) {
                if (a[i] <= last) ok = false;
                last = a[i]; ++len;
            }
            if (ok) best = max(best, len);
        }
        auto ids = lis_indices(a);
        assert((int)ids.size() == best);
        for (int i = 1; i < (int)ids.size(); ++i)
            assert(ids[i - 1] < ids[i] && a[ids[i - 1]] < a[ids[i]]);
    }
}
