#include <bits/stdc++.h>
using namespace std;

#include "../sections/geometry/geometry_base.cpp"
#include "../sections/geometry/convex_hull.cpp"
#include "../sections/geometry/convex_point_query.cpp"

int main() {
    vector<P> p = {{0, 0}, {4, 0}, {5, 2}, {2, 5}, {-1, 3}};
    assert(inConvex(p, {2, 2}, false));
    assert(inConvex(p, {0, 0}, false));
    assert(inConvex(p, {2, 0}, false));
    assert(!inConvex(p, {0, 0}, true));
    assert(!inConvex(p, {2, 0}, true));
    assert(!inConvex(p, {6, 2}, false));
    assert(!inConvex(p, {-2, 3}, false));

    vector<P> one = {{1, 1}};
    assert(inConvex(one, {1, 1}, false));
    assert(!inConvex(one, {1, 1}, true));
    assert(!inConvex(one, {1, 2}, false));

    vector<P> seg = {{0, 0}, {2, 0}};
    assert(inConvex(seg, {1, 0}, false));
    assert(!inConvex(seg, {1, 0}, true));
    assert(!inConvex(seg, {3, 0}, false));

    vector<P> hull = convexHull({{0, 0}, {2, 0}, {2, 2}, {0, 2}, {1, 1}});
    assert(inConvex(hull, {1, 1}, true));
    assert(inConvex(hull, {2, 1}, false));
    assert(!inConvex(hull, {2, 1}, true));
}
