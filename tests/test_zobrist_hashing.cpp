#include <bits/stdc++.h>
using namespace std;

#include "../sections/misc/zobrist_hashing.cpp"

int main() {
    Zobrist z(5, 4, 12345);
    vector<int> a = {0, 1, -1, 2, 3};
    vector<int> b = a;
    assert(z.hash(a) == z.hash(b));

    uint64_t h = z.hash(a);
    h ^= z.key[1][1];
    a[1] = -1;
    assert(h == z.hash(a));

    h ^= z.key[1][2];
    a[1] = 2;
    assert(h == z.hash(a));

    h ^= z.key[1][2];
    h ^= z.key[1][1];
    a[1] = 1;
    assert(h == z.hash(a));

    vector<int> c = {0, 1, -1, 2, 0};
    assert(z.hash(c) != z.hash(a));
}
