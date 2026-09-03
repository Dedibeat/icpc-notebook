#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/fast_knapsack_subset_sum.cpp"

int main() {
    vector<int> a = {0, 1, 1, 3};
    auto bits = subset_sum_bitset<20>(a);
    auto can = subset_sum_sqrt(a);
    auto mn = subset_sum_min_items_sqrt(a);
    for (int s = 0; s <= 5; ++s) assert(bits[s] == (bool)can[s]);
    assert(mn[0] == 0 && mn[2] == 2 && mn[3] == 1 && mn[5] == 3);

    mt19937 rng(1);
    for (int it = 0; it < 300; ++it) {
        int n = rng() % 11;
        vector<int> v(n);
        int S = 0;
        for (int& x : v) x = rng() % 9, S += x;
        vector<int> brute(S + 1, SUBSET_INF); brute[0] = 0;
        for (int x : v) for (int s = S; s >= x; --s)
            if (brute[s - x] < SUBSET_INF) brute[s] = min(brute[s], brute[s - x] + 1);
        auto got = subset_sum_min_items_sqrt(v);
        auto reach = subset_sum_sqrt(v);
        for (int s = 0; s <= S; ++s) {
            assert((brute[s] < SUBSET_INF) == (bool)reach[s]);
            assert(brute[s] == got[s]);
        }
    }

    vector<BoundedItem> items = {{2, 3, 5}, {3, 2, 8}, {0, 2, 4}};
    assert(bounded_knapsack(7, items) == 5 + 5 + 8 + 4 + 4);
    for (int it = 0; it < 200; ++it) {
        int cap = rng() % 16, n = rng() % 6;
        vector<BoundedItem> x(n);
        vector<long long> dp(cap + 1);
        for (auto& e : x) {
            e = {(int)(rng() % 6), (int)(rng() % 4), (long long)((int)(rng() % 13) - 3)};
            for (int copy = 0; copy < e.count; ++copy) {
                if (e.weight == 0) {
                    if (e.value > 0) for (auto& z : dp) z += e.value;
                } else for (int c = cap; c >= e.weight; --c)
                    dp[c] = max(dp[c], dp[c - e.weight] + e.value);
            }
        }
        assert(bounded_knapsack(cap, x) == dp[cap]);
    }
}
