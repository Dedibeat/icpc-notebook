// Exact LCS length of two byte strings; no subsequence reconstruction.
// Time O((|a|+256)*ceil(|b|/64)+|b|), memory O(256*ceil(|b|/64)).
// Unsigned arithmetic is intentional: borrow and shift carry cross words.
// Usage: bitLCS("banana", "ananas") == 5. Includes embedded zero/high bytes.
#include "common.hpp"

int bitLCS(const string& a, const string& b) {
    int words = (b.size()+63)/64;
    vector<vector<ull>> match(256, vector<ull>(words));
    for (int j = 0; j < (int)b.size(); ++j)
        match[(unsigned char)b[j]][j/64] |= 1ULL << (j%64);
    vector<ull> s(words);
    for (unsigned char c : a) {
        ull carry = 1, borrow = 0;
        for (int j = 0; j < words; ++j) {
            ull old = s[j], x = old | match[c][j];
            ull y = (old << 1) | carry;
            carry = old >> 63;
            ull z = x-y, next = (x < y) | (z < borrow);
            z -= borrow; borrow = next;
            s[j] = x & ~z;
        }
    }
    int ans = 0;
    for (ull x : s) ans += __builtin_popcountll(x);
    return ans;
}
