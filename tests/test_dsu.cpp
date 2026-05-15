#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/dsu.cpp"

int main() {
    DSU d(5);
    assert(d.size(0) == 1);
    assert(d.unite(0, 1));
    assert(!d.unite(1, 0));
    assert(d.same(0, 1));
    assert(d.size(0) == 2 && d.size(1) == 2);
    assert(d.unite(2, 3));
    assert(d.unite(1, 2));
    assert(d.same(0, 3));
    assert(!d.same(0, 4));
    assert(d.size(3) == 4);
    d.init(3);
    assert(!d.same(0, 1) && d.size(2) == 1);
}
