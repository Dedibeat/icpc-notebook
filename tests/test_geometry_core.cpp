#include <bits/stdc++.h>
using namespace std;

#include "../sections/geometry/geometry_base.cpp"
#include "../sections/geometry/convex_hull.cpp"

bool close(T a, T b, T eps = 1e-9) {
    return fabsl(a - b) <= eps;
}

bool same(P a, P b, T eps = 1e-9) {
    return close(a.x, b.x, eps) && close(a.y, b.y, eps);
}

int main() {
    assert(ori({0, 0}, {1, 0}, {1, 1}) == 1);
    assert(ori({0, 0}, {1, 0}, {1, -1}) == -1);
    assert(ori({0, 0}, {1, 0}, {2, 0}) == 0);

    assert(onSegment({0, 0}, {2, 0}, {1, 0}));
    assert(!onSegment({0, 0}, {2, 0}, {3, 0}));
    assert(segInter({0, 0}, {2, 0}, {1, 0}, {3, 0})); // overlap
    assert(segInter({0, 0}, {1, 1}, {1, 1}, {2, 0})); // endpoint
    assert(!segInter({0, 0}, {1, 0}, {2, 0}, {3, 0}));
    assert(segInter({0, 0}, {2, 2}, {0, 2}, {2, 0}));

    P li = lineInter({0, 0}, {2, 2}, {0, 2}, {2, 0});
    assert(same(li, {1, 1}));
    assert(close(distLine({0, 0}, {2, 0}, {1, 3}), 3));
    assert(close(distSegment({0, 0}, {2, 0}, {3, 4}), 4.1231056256176605L));
    assert(close(distSegment({0, 0}, {0, 0}, {3, 4}), 5));

    vector<P> sq = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    assert(close(area2(sq), 8));
    reverse(sq.begin(), sq.end());
    assert(close(area2(sq), -8));
    reverse(sq.begin(), sq.end());
    assert(inPoly(sq, {1, 1}) == 1);
    assert(inPoly(sq, {3, 1}) == 0);
    assert(inPoly(sq, {2, 1}) == 2);
    assert(inPoly(sq, {0, 0}) == 2);

    vector<P> pts = {{0, 0}, {1, 0}, {2, 0}, {2, 2}, {1, 1}, {0, 2}, {0, 0}};
    vector<P> h = convexHull(pts);
    assert((int)h.size() == 4);
    assert(same(h[0], {0, 0}) && same(h[1], {2, 0}) && same(h[2], {2, 2}) && same(h[3], {0, 2}));
    assert(close(diameter2(h), 8));

    vector<P> col = {{0, 0}, {1, 0}, {2, 0}, {2, 0}, {-1, 0}};
    h = convexHull(col);
    assert((int)h.size() == 2);
    assert(same(h[0], {-1, 0}) && same(h[1], {2, 0}));

    vector<P> cl = circleLine({0, 0}, 5, {-10, 0}, {10, 0});
    assert((int)cl.size() == 2);
    assert(close(norm(cl[0]), 5) && close(norm(cl[1]), 5));
    cl = circleLine({0, 0}, 5, {-10, 5}, {10, 5});
    assert((int)cl.size() == 1 && same(cl[0], {0, 5}));
    cl = circleLine({0, 0}, 5, {-10, 6}, {10, 6});
    assert(cl.empty());

    vector<P> cc = circleCircle({0, 0}, 5, {8, 0}, 5);
    assert((int)cc.size() == 2);
    assert(close(norm(cc[0]), 5) && close(norm(cc[0] - P{8, 0}), 5));
    cc = circleCircle({0, 0}, 5, {10, 0}, 5);
    assert((int)cc.size() == 1 && same(cc[0], {5, 0}));
    assert(circleCircle({0, 0}, 5, {20, 0}, 5).empty());
    assert(circleCircle({0, 0}, 5, {0, 0}, 5).empty());
}
