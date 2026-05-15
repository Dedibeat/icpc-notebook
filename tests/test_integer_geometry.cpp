#include <bits/stdc++.h>
using namespace std;

#include "../sections/geometry/integer_geometry.cpp"

int main() {
    assert(ori_i({0, 0}, {1, 0}, {1, 1}) == 1);
    assert(ori_i({0, 0}, {1, 0}, {1, -1}) == -1);
    assert(ori_i({0, 0}, {1, 0}, {5, 0}) == 0);

    IP a{1000000000LL, 1000000000LL};
    IP b{-1000000000LL, 1000000000LL};
    IP c{1000000000LL, -1000000000LL};
    assert(ori_i(a, b, c) == 1);

    IP d{-1000000000LL, -1000000000LL};
    i128 area = cross_i(a, b, d);
    assert(area == (i128)4000000000000000000LL);
}
