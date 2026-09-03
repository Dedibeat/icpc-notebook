// Fast bounded knapsack and subset-sum variants.
// Complexity: bitset O(items*SUM/64); compressed DP O(S*D), D <= sqrt(2S).
// Pitfalls: all weights are nonnegative; zero weights need special handling.
// Usage: subset_sum_sqrt(a), subset_sum_min_items_sqrt(a), bounded_knapsack(C,it).
const int SUBSET_INF = 1e9;

template<size_t MAX_SUM>
bitset<MAX_SUM + 1> subset_sum_bitset(const vector<int>& a) {
    bitset<MAX_SUM + 1> can;
    can[0] = 1;
    for (int x : a) if (0 <= x && x <= (int)MAX_SUM) can |= can << x;
    return can;
}

vector<pair<int, int>> compress_positive(const vector<int>& a, int& sum) {
    sum = 0;
    for (int x : a) if (x > 0) sum += x;
    vector<int> freq(sum + 1);
    for (int x : a) if (x > 0) ++freq[x];
    vector<pair<int, int>> items;
    for (int w = 1; w <= sum; ++w) if (freq[w]) items.push_back({w, freq[w]});
    return items;
}

vector<char> subset_sum_sqrt(const vector<int>& a) {
    int S;
    auto items = compress_positive(a, S);
    vector<char> dp(S + 1), ndp(S + 1);
    dp[0] = 1;
    for (auto [w, cnt] : items) {
        fill(ndp.begin(), ndp.end(), 0);
        for (int r = 0; r < w && r <= S; ++r) {
            int window = 0;
            for (int s = r, t = 0; s <= S; s += w, ++t) {
                window += dp[s];
                if (t > cnt) window -= dp[s - (cnt + 1) * w];
                ndp[s] = window > 0;
            }
        }
        dp.swap(ndp);
    }
    return dp;
}

vector<int> subset_sum_min_items_sqrt(const vector<int>& a) {
    int S;
    auto items = compress_positive(a, S);
    vector<int> dp(S + 1, SUBSET_INF), ndp(S + 1);
    dp[0] = 0;
    for (auto [w, cnt] : items) {
        fill(ndp.begin(), ndp.end(), SUBSET_INF);
        for (int r = 0; r < w && r <= S; ++r) {
            deque<pair<int, int>> q; // (dp[s]-t, t)
            for (int s = r, t = 0; s <= S; s += w, ++t) {
                while (!q.empty() && q.front().second < t - cnt) q.pop_front();
                if (dp[s] < SUBSET_INF) {
                    int val = dp[s] - t;
                    while (!q.empty() && q.back().first >= val) q.pop_back();
                    q.push_back({val, t});
                }
                if (!q.empty()) ndp[s] = q.front().first + t;
            }
        }
        dp.swap(ndp);
    }
    return dp;
}

struct BoundedItem { int weight, count; long long value; };

long long bounded_knapsack(int cap, const vector<BoundedItem>& items) {
    vector<long long> dp(cap + 1), ndp(cap + 1);
    for (auto [w, cnt, val] : items) {
        if (w == 0) {
            if (val > 0) for (long long& x : dp) x += val * cnt;
            continue;
        }
        ndp = dp;
        for (int r = 0; r < w && r <= cap; ++r) {
            deque<pair<long long, int>> q;
            for (int c = r, t = 0; c <= cap; c += w, ++t) {
                while (!q.empty() && q.front().second < t - cnt) q.pop_front();
                long long cur = dp[c] - 1LL * t * val;
                while (!q.empty() && q.back().first <= cur) q.pop_back();
                q.push_back({cur, t});
                ndp[c] = q.front().first + 1LL * t * val;
            }
        }
        dp.swap(ndp);
    }
    return dp[cap];
}
