#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/lazy_segment_tree.cpp"

int main() {
    // default config: range add, range sum, inclusive [l, r]
    vector<long long> a = {1, 2, 3, 4, 5};
    SegTree st;
    st.init(a);
    assert(st.query(0, 4) == 15);
    st.update(1, 3, 10);
    assert(st.query(0, 4) == 45);
    assert(st.query(2, 2) == 13);
    st.update(0, 0, -1);
    assert(st.query(0, 0) == 0);
    assert(st.query(0, 1) == 12);

    // randomized vs brute force
    mt19937 rng(99);
    int n = 60;
    vector<long long> b(n);
    for (auto& x : b) x = (long long)(rng() % 100) - 50;
    SegTree rt;
    rt.init(b);
    for (int it = 0; it < 3000; it++) {
        int l = rng() % n, r = l + rng() % (n - l);
        if (rng() % 2) {
            long long f = (long long)(rng() % 20) - 10;
            rt.update(l, r, f);
            for (int i = l; i <= r; i++) b[i] += f;
        } else {
            long long sum = 0;
            for (int i = l; i <= r; i++) sum += b[i];
            assert(rt.query(l, r) == sum);
        }
    }
    st.init(vector<long long>{});
    assert(st.query(0, -1) == 0);
    st.update(0, -1, 7);
    st.init(vector<long long>{5});
    st.update(0, 0, -5);
    assert(st.query(0, 0) == 0);
    assert(st.query(1, 0) == 0);
    return 0;
}
