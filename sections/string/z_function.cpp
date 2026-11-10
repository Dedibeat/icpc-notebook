// z[i] is the length of the prefix matching s starting at i; z[0]=0.
// O(n) time/memory. Empty input returns {}; internal window is [l,r).
// Matching pitfall: a separator in pattern + separator + text must be absent.
// Example: z_function("aaaa") == vector<int>({0,3,2,1}).
vector<int> z_function(const string& s) {
    int n = s.size(), l = 0, r = 0;
    vector<int> z(n);
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
