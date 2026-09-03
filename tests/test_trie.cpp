#include <bits/stdc++.h>
using namespace std;
#include "../sections/string/trie.cpp"

int main() {
    Trie t;
    t.insert(""); t.insert("ab"); t.insert("abc"); t.insert("ab");
    assert(t.count_word("") == 1);
    assert(t.count_word("ab") == 2 && t.count_word("a") == 0);
    assert(t.count_prefix("ab") == 3 && t.count_prefix("x") == 0);

    BinaryTrie b;
    multiset<unsigned long long> s;
    for (auto x : {0ULL, 5ULL, 5ULL, (1ULL<<62)}) b.insert(x), s.insert(x);
    for (auto q : {0ULL, 2ULL, 9ULL, (1ULL<<62)-1}) {
        unsigned long long want = 0;
        for (auto x : s) want = max(want, x ^ q);
        assert(b.max_xor(q) == want);
    }
    b.erase(5); s.erase(s.find(5));
    b.erase(5); s.erase(s.find(5));
    assert(b.max_xor(2) == ((1ULL<<62) ^ 2));
}
