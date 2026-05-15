#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/short_segment_tree.cpp"

int main() {
    n = 4;
    fill(t, t + 2 * N, 0);
    t[n + 0] = 1000000000LL;
    t[n + 1] = 1000000000LL;
    t[n + 2] = 1000000000LL;
    t[n + 3] = 1000000000LL;
    build();

    assert(query(0, 4) == 4000000000LL);
    assert(query(1, 3) == 2000000000LL);
    assert(query(2, 2) == 0);

    modify(1, -5);
    assert(query(0, 2) == 999999995LL);
    assert(query(1, 2) == -5);
}
