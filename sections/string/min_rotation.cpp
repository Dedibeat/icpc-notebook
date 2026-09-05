// Booth's algorithm: start index of the lexicographically smallest cyclic
// rotation. O(n) time, O(n) memory; empty string returns 0.
// Example: min_rotation("baca")==3 because "abac" is smallest.
int min_rotation(string s) {
    s += s;
    int n = s.size(), i = 0, ans = 0;

    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;

        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else k++;
            j++;
        }

        while (i <= k) i += j - k;
    }

    return ans;
}
