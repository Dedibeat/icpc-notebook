#include <bits/stdc++.h>
using namespace std;

#include "../sections/geometry/geometry_base.cpp"
#include "../sections/geometry/convex_hull.cpp"
#include "../sections/geometry/circle_tangents.cpp"

bool close(T a, T b) {
    return fabsl(a - b) < 1e-9;
}

int main() {
    auto t = circleTangents({0, 0}, 5, {13, 0}, 0);
    assert((int)t.size() == 2);
    for (auto [a, b] : t) {
        assert(close(norm(a), 5));
        assert(close(dot(a, b - a), 0));
        assert(close(b.x, 13) && close(b.y, 0));
    }

    t = circleTangents({0, 0}, 5, {5, 0}, 0);
    assert((int)t.size() == 1);
    assert(close(t[0].first.x, 5) && close(t[0].first.y, 0));

    assert(circleTangents({0, 0}, 5, {3, 0}, 0).empty());
    assert(circleTangents({0, 0}, 5, {0, 0}, 0).empty());

    t = circleTangents({0, 0}, 2, {6, 0}, 2);
    assert((int)t.size() == 2);
    for (auto [a, b] : t) {
        assert(close(norm(a), 2));
        assert(close(norm(b - P{6, 0}), 2));
        assert(close(dot(a, b - a), 0));
    }
}
