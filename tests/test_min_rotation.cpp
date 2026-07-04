#include <bits/stdc++.h>
using namespace std;

#include "../sections/string/min_rotation.cpp"

int bruteMinRotation(const string& s) {
    int n = s.size(), best = 0;
    string bs = s;
    for (int i = 1; i < n; i++) {
        string cur = s.substr(i) + s.substr(0, i);
        if (cur < bs) { bs = cur; best = i; }
    }
    return best;
}

int main() {
    mt19937 rng(17);
    for (int it = 0; it < 3000; it++) {
        int n = 1 + rng() % 12;
        int alpha = 1 + rng() % 3; // small alphabets stress ties/periodicity
        string s(n, 'a');
        for (auto& c : s) c = 'a' + rng() % alpha;
        int got = min_rotation(s), want = bruteMinRotation(s);
        // compare rotations, not indices (ties may differ)
        string rg = s.substr(got) + s.substr(0, got);
        string rw = s.substr(want) + s.substr(0, want);
        assert(rg == rw);
    }
    assert(min_rotation("a") == 0);
    assert(min_rotation("ba") == 1);
    string allsame(50, 'z');
    string r = allsame;
    int idx = min_rotation(allsame);
    assert(idx >= 0 && idx < 50);
    return 0;
}
