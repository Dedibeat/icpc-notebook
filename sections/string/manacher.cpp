// p[i] = # odd palindromes centered at i; longest has length 2*p[i]-1.
// For BOTH odd and even: run on t = "#a#b#c#" (insert '#' between chars and at
// both ends); then longest palindrome centered in t at i has length p[i]-1.
// Sentinels are bytes 1 and 2, so any printable input is safe (using '$'/'^'
// as sentinels breaks on inputs that contain those characters).
vector<int> manacher_odd(string s) {
    int n = s.size();
    s = char(1) + s + char(2);
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = min(r - i, p[l + (r - i)]);
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
