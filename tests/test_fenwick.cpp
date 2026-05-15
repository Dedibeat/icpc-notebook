#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/fenwick.cpp"

int main() {
    Fenwick fw(5);
    vector<long long> a(5);
    auto add = [&](int i, long long x) { fw.add(i, x); a[i] += x; };
    add(0, 3);
    add(1, 1);
    add(3, 4);
    add(4, 2);
    for (int l = 0; l <= 5; l++) for (int r = l; r <= 5; r++) {
        long long s = 0;
        for (int i = l; i < r; i++) s += a[i];
        assert(fw.rangeSum(l, r) == s);
    }
    assert(fw.lower_bound(1) == 0);
    assert(fw.lower_bound(3) == 0);
    assert(fw.lower_bound(4) == 1);
    assert(fw.lower_bound(5) == 3);
    assert(fw.lower_bound(10) == 4);
    assert(fw.lower_bound(11) == 5);
    add(1, 5);
    assert(fw.rangeSum(0, 2) == 9);
}
