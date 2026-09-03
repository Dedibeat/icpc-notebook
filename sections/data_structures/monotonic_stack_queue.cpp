// Monotonic stack boundaries and sliding-window maximum.
// Complexity: O(n); every index enters and leaves once.
// Pitfalls: duplicate tie rule is asymmetric: left < a[i], right <= a[i].
// Usage: auto [left,right]=smaller_bounds(a); auto mx=sliding_max(a,k);
pair<vector<int>, vector<int>> smaller_bounds(const vector<long long>& a) {
    int n = (int)a.size();
    vector<int> left(n, -1), right(n, n), st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] >= a[i]) {
            right[st.back()] = i;
            st.pop_back();
        }
        if (!st.empty()) left[i] = st.back();
        st.push_back(i);
    }
    return {left, right};
}

vector<long long> sliding_max(const vector<long long>& a, int k) {
    if (k <= 0 || k > (int)a.size()) return {};
    deque<int> q;
    vector<long long> ans;
    for (int i = 0; i < (int)a.size(); ++i) {
        while (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        if (i + 1 >= k) ans.push_back(a[q.front()]);
    }
    return ans;
}
