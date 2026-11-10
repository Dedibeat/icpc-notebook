// First k subset sums in sorted order (CSES 3108, entry 13897226).
// Include the empty subset and keep one sum per subset of indices.
// Usage: k_smallest_subset_sums({1, -3, 3}, 4) -> {-3, -2, 0, 0}.
// O(n log n + k log(k+1)) time and O(n+k) space.
vector<__int128> k_smallest_subset_sums(const vector<long long>& a, int k) {
    if (k <= 0) return {};
    vector<__int128> w(a.begin(), a.end());
    __int128 base = 0;
    for (auto& x : w) if (x < 0) {
        base += x;
        x = -x;
    }
    sort(w.begin(), w.end());

    // Start with all negatives selected. Toggling index i costs w[i].
    // A toggle set with max j has one parent. Remove j if j == 0 or
    // j-1 is present. Otherwise replace j with j-1.
    using State = pair<__int128, int>;  // sum, largest toggled index
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({base, -1});
    vector<__int128> ans;
    int n = w.size();
    for (; k > 0 && !pq.empty(); --k) {
        auto [sum, i] = pq.top();
        pq.pop();
        ans.push_back(sum);
        if (i + 1 == n) continue;
        pq.push({sum + w[i + 1], i + 1});  // Add i+1.
        if (i >= 0) pq.push({sum + w[i + 1] - w[i], i + 1});
    }
    return ans;
}
