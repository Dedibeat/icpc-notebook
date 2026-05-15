// Kasai LCP array from string s and suffix array sa.
// lcp[i] = LCP(sa[i], sa[i+1]), size max(0, n-1).
// Time: O(n). Source: standard Kasai algorithm (cp-algorithms/USACO Guide).
vector<int> lcp_array(const string& s, const vector<int>& sa) {
    int n = (int)s.size();
    if (n == 0) return {};
    vector<int> rank(n), lcp(max(0, n - 1));
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; i++) {
        int r = rank[i];
        if (r == n - 1) {
            h = 0;
            continue;
        }
        int j = sa[r + 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[r] = h;
        if (h) h--;
    }
    return lcp;
}
