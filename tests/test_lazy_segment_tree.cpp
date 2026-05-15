#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/lazy_segment_tree.cpp"

int main() {
    vector<long long> a = {1, 2, 3, 4, 5};
    segTree st(a.size());
    st.build(a, 1, 0, (int)a.size() - 1);
    assert(st.range_query(1, 0, 4, 0, 4) == 15);
    st.assign_range(1, 0, 4, 1, 3, 0);
    assert(st.range_query(1, 0, 4, 0, 4) == 6);
    assert(st.point_query(1, 0, 4, 2) == 0);
    st.assign_range(1, 0, 4, 2, 4, -2);
    assert(st.range_query(1, 0, 4, 0, 4) == -5);
    assert(st.range_query(1, 0, 4, 3, 4) == -4);
}
