#include <bits/stdc++.h>
using namespace std;

#include "../sections/string/suffix_array.cpp"

vector<int> brute_cyclic(string s) {
    vector<int> p(s.size());
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int a, int b) {
        for (int k = 0; k < (int)s.size(); k++) {
            unsigned char ca = s[(a + k) % s.size()];
            unsigned char cb = s[(b + k) % s.size()];
            if (ca != cb) return ca < cb;
        }
        return false;
    });
    return p;
}

int main() {
    assert(sort_cyclic_shifts("").empty());

    string s = "banana$";
    assert(sort_cyclic_shifts(s) == brute_cyclic(s));

    string bytes;
    bytes.push_back(char(255));
    bytes.push_back('\0');
    bytes.push_back('a');
    bytes.push_back(char(200));
    assert(sort_cyclic_shifts(bytes) == brute_cyclic(bytes));
}
