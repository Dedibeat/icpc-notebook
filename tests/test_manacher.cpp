#include <bits/stdc++.h>
using namespace std;

#include "../sections/string/manacher.cpp"

int bruteOddRadius(const string& s, int i) {
    int n = s.size(), p = 0;
    while (i - p >= 0 && i + p < n && s[i - p] == s[i + p]) p++;
    return p; // matches manacher convention: # odd palindromes centered at i
}

int main() {
    // random strings, small alphabet
    mt19937 rng(31);
    for (int it = 0; it < 500; it++) {
        int n = 1 + rng() % 30;
        string s(n, 'a');
        for (auto& c : s) c = 'a' + rng() % 2;
        auto p = manacher_odd(s);
        assert((int)p.size() == n);
        for (int i = 0; i < n; i++) assert(p[i] == bruteOddRadius(s, i));
    }

    // inputs containing the OLD sentinel characters '$' and '^' must work
    for (string s : {string("$$$"), string("^^^"), string("a$a^a"),
                     string("$aba^"), string("^$^$^")}) {
        auto p = manacher_odd(s);
        for (int i = 0; i < (int)s.size(); i++)
            assert(p[i] == bruteOddRadius(s, i));
    }

    // the '#' transform trick for both parities
    string s = "abaab";
    string t = "#";
    for (char c : s) { t += c; t += '#'; }
    auto p = manacher_odd(t);
    int best = 0;
    for (int i = 0; i < (int)t.size(); i++) best = max(best, p[i] - 1);
    assert(best == 4); // longest palindromic substring of "abaab" is "baab"
    return 0;
}
