#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/sparse_table.cpp"

int main() {
    vector<long long> a = {5, -1, 7, -1, 3, 9};
    SparseTable st(a);
    for (int l = 0; l < (int)a.size(); l++) for (int r = l + 1; r <= (int)a.size(); r++) {
        long long want = *min_element(a.begin() + l, a.begin() + r);
        assert(st.query(l, r) == want);
    }
    SparseTable one(vector<long long>{42});
    assert(one.query(0, 1) == 42);

    // Random sizes incl. empty and powers of two; reuse one object (smaller rebuilds).
    mt19937 rng(7);
    SparseTable re;
    for (int n : {0, 1, 2, 3, 4, 7, 8, 9, 16, 31, 32, 33, 64, 65, 5, 0, 2}) {
        vector<long long> b(n);
        for (auto& x : b) x = (long long)(rng() % 21) - 10 + (rng() % 2 ? LLONG_MIN / 2 : 0);
        re.build(b);
        for (int l = 0; l < n; l++) for (int r = l + 1; r <= n; r++)
            assert(re.query(l, r) == *min_element(b.begin() + l, b.begin() + r));
    }
}
