#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/dsu_on_segtree.cpp"

int main() {
    mt19937 rng(606);
    // several sets of points; random inserts, queries, merges vs multiset brute
    const int SETS = 8;
    vector<int> root(SETS, 0);
    vector<multiset<int>> brute(SETS);
    tp = 1;

    auto bruteCount = [&](int s, int l, int r) {
        int c = 0;
        for (int x : brute[s]) c += (x >= l && x < r);
        return c;
    };

    int alive = SETS;
    for (int it = 0; it < 20000; it++) {
        int op = rng() % 3;
        int s = rng() % SETS;
        if (op == 0) {
            int pos = rng() % 1000000000;
            upd(root[s], pos, +1);
            brute[s].insert(pos);
        } else if (op == 1) {
            int l = rng() % 1000000000, r = rng() % 1000000000;
            if (l > r) swap(l, r);
            assert(query(root[s], l, r) == bruteCount(s, l, r));
        } else if (alive > 1 && rng() % 50 == 0) {
            int t = rng() % SETS;
            if (t == s || brute[t].empty()) continue;
            root[s] = merge(root[s], root[t]);
            for (int x : brute[t]) brute[s].insert(x);
            brute[t].clear();
            root[t] = 0;
        }
    }
    // full-range totals
    for (int s = 0; s < SETS; s++)
        assert(query(root[s], 0, POSMAX + 1) == (int)brute[s].size());

    // boundary positions
    tp = 1;
    int r0 = 0;
    upd(r0, 0, +1);
    upd(r0, POSMAX, 3'000'000'000LL);
    assert(query(r0, 0, 0) == 0);
    assert(query(r0, 0, 1) == 1);
    assert(query(r0, POSMAX, POSMAX + 1) == 3'000'000'000LL);
    assert(query(r0, 1, POSMAX) == 0);
    return 0;
}
