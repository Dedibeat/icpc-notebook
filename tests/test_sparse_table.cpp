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
}
