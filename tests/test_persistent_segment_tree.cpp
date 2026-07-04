#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/persistent_segment_tree.cpp"

int main() {
    mt19937 rng(555);
    for (int it = 0; it < 100; it++) {
        int n = 1 + rng() % 50, M = 1 + rng() % 30;
        vector<int> a(n);
        for (auto& x : a) x = rng() % M;

        PST st(M);
        vector<int> root(n + 1, 0);
        for (int i = 0; i < n; i++) root[i + 1] = st.upd(root[i], a[i]);

        for (int q = 0; q < 50; q++) {
            int l = rng() % n, r = l + 1 + rng() % (n - l);
            vector<int> sub(a.begin() + l, a.begin() + r);
            sort(sub.begin(), sub.end());
            int k = 1 + rng() % (r - l);
            assert(st.kth(root[l], root[r], k) == sub[k - 1]);

            int lo = rng() % M, hi = lo + rng() % (M - lo + 1);
            int expect = 0;
            for (int i = l; i < r; i++) expect += (a[i] >= lo && a[i] < hi);
            assert(st.cnt(root[r], lo, hi) - st.cnt(root[l], lo, hi) == expect);
        }
    }
    // single element, M = 1
    PST st(1);
    int r1 = st.upd(0, 0);
    assert(st.kth(0, r1, 1) == 0);
    assert(st.cnt(r1, 0, 1) == 1);
    return 0;
}
