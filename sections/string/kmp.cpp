// Prefix function: pi[i] is the longest proper prefix of s[0..i] that is a suffix.
// O(n) time/memory. Empty input returns {}; pi[0]=0.
// Matching pitfall: a separator in pattern + separator + text must be absent.
// Example: prefix_function("ababa") == vector<int>({0,0,1,2,3}).
vector<int> prefix_function(const string& s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
