#include <bits/stdc++.h>
using namespace std;

#include "../sections/string/Aho.cpp"

long long bruteCount(const vector<string>& pats, const string& text) {
    long long total = 0;
    for (const string& p : pats)
        for (int i = 0; i + (int)p.size() <= (int)text.size(); i++)
            total += text.compare(i, p.size(), p) == 0;
    return total;
}

int main() {
    {
        Aho a;
        a.add("a");
        a.add("ab");
        a.add("bab");
        a.build();
        assert(a.countMatches("abab") == bruteCount({"a", "ab", "bab"}, "abab"));
    }
    {
        // duplicate patterns count twice; pattern = suffix of another
        Aho a;
        a.add("aa");
        a.add("aa");
        a.add("aaa");
        a.build();
        assert(a.countMatches("aaaa") == bruteCount({"aa", "aa", "aaa"}, "aaaa"));
    }
    // randomized vs brute force
    mt19937 rng(2468);
    for (int it = 0; it < 200; it++) {
        int np = 1 + rng() % 6;
        vector<string> pats;
        Aho a;
        for (int i = 0; i < np; i++) {
            int len = 1 + rng() % 5;
            string p(len, 'a');
            for (auto& c : p) c = 'a' + rng() % 3;
            pats.push_back(p);
            a.add(p);
        }
        a.build();
        int tl = 1 + rng() % 60;
        string text(tl, 'a');
        for (auto& c : text) c = 'a' + rng() % 3;
        assert(a.countMatches(text) == bruteCount(pats, text));
    }
    return 0;
}
