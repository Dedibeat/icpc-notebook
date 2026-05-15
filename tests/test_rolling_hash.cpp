#include <bits/stdc++.h>
using namespace std;

#include "../sections/string/rolling_hash.cpp"

int main() {
    string s = "abcabc";
    Hash h(s);
    assert(h.get(0, 3) == h.get(3, 6));
    assert(h.get(0, 2) != h.get(1, 3));

    string bytes;
    bytes.push_back(char(255));
    bytes.push_back('x');
    bytes.push_back(char(255));
    bytes.push_back('x');
    Hash hb(bytes);
    assert(hb.get(0, 2) == hb.get(2, 4));
    assert(hb.get(0, 1) != hb.get(1, 2));
}
