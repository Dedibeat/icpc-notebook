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

    // Thue-Morse anti-test: A != B but mod-2^64 overflow hashing collides
    // for EVERY base. The prime-mod hash must distinguish them.
    string A = "a", B = "b";
    for (int i = 0; i < 11; i++) {
        string na = A + B, nb = B + A;
        A = na;
        B = nb;
    }
    assert(A != B && A.size() == 2048);
    uint64_t oa = 0, ob = 0; // the OLD broken scheme, for the record
    for (char c : A) oa = oa * 1000003ULL + (unsigned char)c + 1;
    for (char c : B) ob = ob * 1000003ULL + (unsigned char)c + 1;
    assert(oa == ob); // documented: overflow hashing cannot tell them apart
    Hash ha(A), hbm(B);
    assert(ha.get(0, 2048) != hbm.get(0, 2048));

    // cross-object comparison shares the global base
    Hash h1("xyzxyz"), h2("abxyzq");
    assert(h1.get(0, 3) == h2.get(2, 5));

    // exhaustive: hash equality == substring equality on a random string
    mt19937 rng(1234);
    string r(40, 'a');
    for (auto& c : r) c = 'a' + rng() % 3; // small alphabet -> many repeats
    Hash hr(r);
    int n = r.size();
    for (int l1 = 0; l1 < n; l1++)
        for (int l2 = 0; l2 < n; l2++)
            for (int len = 1; l1 + len <= n && l2 + len <= n; len++) {
                bool same = r.compare(l1, len, r, l2, len) == 0;
                assert((hr.get(l1, l1 + len) == hr.get(l2, l2 + len)) == same);
            }
    return 0;
}
