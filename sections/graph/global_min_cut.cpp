// Stoer-Wagner global min cut. O(n^3) time, O(n^2) memory.
// Input: symmetric matrix of nonnegative capacities, diagonal zero.
// Returns {cut weight, one side}; n < 2 returns {0,{}}.
// All capacity sums must fit long long. Example: {{0,5},{5,0}} gives weight 5.
pair<long long, vector<int>> globalMinCut(vector<vector<long long>> a) {
    int n = a.size();
    if (n < 2) return {0, {}};
    vector<int> active(n);
    iota(active.begin(), active.end(), 0);
    vector<vector<int>> group(n);
    for (int i = 0; i < n; ++i) group[i] = {i};
    pair<long long, vector<int>> best = {LLONG_MAX, {}};
    while (active.size() > 1) {
        vector<long long> weight(n);
        vector<bool> used(n);
        int prev = -1;
        for (int i = 0; i < (int)active.size(); ++i) {
            int at = -1;
            for (int to : active)
                if (!used[to] && (at == -1 || weight[to] > weight[at])) at = to;
            if (i + 1 == (int)active.size()) {
                if (weight[at] <= best.first) best = {weight[at], group[at]};
                for (int to : active) if (to != prev && to != at)
                    a[prev][to] = a[to][prev] = a[prev][to] + a[at][to];
                group[prev].insert(group[prev].end(), group[at].begin(), group[at].end());
                active.erase(find(active.begin(), active.end(), at));
                break;
            }
            used[at] = true;
            for (int to : active) if (!used[to]) weight[to] += a[at][to];
            prev = at;
        }
    }
    return best;
}
