// Reconstruct one strict longest increasing subsequence (indices).
// Complexity: O(n log n).
// Pitfalls: lower_bound gives strict LIS; use upper_bound for nondecreasing LIS.
// Usage: vector<int> ids = lis_indices(a);
vector<int> lis_indices(const vector<long long>& a) {
    vector<long long> tail;
    vector<int> at, parent(a.size(), -1);
    for (int i = 0; i < (int)a.size(); ++i) {
        int p = lower_bound(tail.begin(), tail.end(), a[i]) - tail.begin();
        if (p == (int)tail.size()) tail.push_back(a[i]), at.push_back(i);
        else tail[p] = a[i], at[p] = i;
        if (p) parent[i] = at[p - 1];
    }
    vector<int> ans;
    if (!at.empty()) for (int v = at.back(); v != -1; v = parent[v]) ans.push_back(v);
    reverse(ans.begin(), ans.end());
    return ans;
}
