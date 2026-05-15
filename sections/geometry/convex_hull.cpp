// Core 2D geometry routines. Depends on geometry_base.cpp.
// Sources: KACTL OnSegment/LineIntersection/InsidePolygon/ConvexHull/HullDiameter/CircleLine/CircleIntersection style.
// Complexity: listed per function below. Uses 0-indexed vectors.
// Usage: copy geometry_base.cpp first.

// segment intersection. O(1).
// Pitfalls: segInter only says yes/no; overlapping intersection needs separate handling.
bool segInter(P a, P b, P c, P d) {
    int oa = ori(c, d, a), ob = ori(c, d, b);
    int oc = ori(a, b, c), od = ori(a, b, d);
    if (oa == 0 && onSegment(c, d, a)) return true;
    if (ob == 0 && onSegment(c, d, b)) return true;
    if (oc == 0 && onSegment(a, b, c)) return true;
    if (od == 0 && onSegment(a, b, d)) return true;
    return oa * ob < 0 && oc * od < 0;
}

// line intersection/projection/distances. O(1).
// Pitfalls: lineInter assumes non-parallel non-zero-length lines.
P lineInter(P a, P b, P c, P d) {
    P r = b - a, s = d - c;
    return a + r * (cross(c - a, s) / cross(r, s));
}

P projLine(P a, P b, P p) {
    P ab = b - a;
    return a + ab * (dot(p - a, ab) / norm2(ab));
}

T distLine(P a, P b, P p) {
    return abs(cross(b - a, p - a)) / norm(b - a);
}

T distSegment(P a, P b, P p) {
    if (a == b) return norm(p - a);
    if (sgn(dot(p - a, b - a)) <= 0) return norm(p - a);
    if (sgn(dot(p - b, a - b)) <= 0) return norm(p - b);
    return distLine(a, b, p);
}

// polygon signed double-area. O(n).
// Pitfalls: clockwise order gives negative area.
T area2(const vector<P>& p) {
    T s = 0;
    for (int i = 0, n = (int)p.size(); i < n; i++) s += cross(p[i], p[(i + 1) % n]);
    return s;
}

// point in polygon: 0 outside, 1 inside, 2 boundary. O(n).
// Pitfalls: works for simple polygons; boundary is checked first.
int inPoly(const vector<P>& poly, P q) {
    bool in = false;
    int n = (int)poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        P a = poly[i], b = poly[j];
        if (onSegment(a, b, q)) return 2;
        bool cond = (a.y > q.y) != (b.y > q.y);
        if (cond) {
            T x = a.x + (b.x - a.x) * (q.y - a.y) / (b.y - a.y);
            if (sgn(x - q.x) > 0) in = !in;
        }
    }
    return in;
}

// convex hull in CCW order. O(n log n).
// Pitfalls: <= removes collinear boundary points; change to < to keep them.
vector<P> convexHull(vector<P> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    if ((int)p.size() <= 1) return p;
    vector<P> h;
    for (P pt : p) {
        while ((int)h.size() >= 2 && sgn(cross(h[(int)h.size() - 2], h.back(), pt)) <= 0)
            h.pop_back();
        h.push_back(pt);
    }
    int lower = (int)h.size();
    for (int i = (int)p.size() - 2; i >= 0; i--) {
        P pt = p[i];
        while ((int)h.size() > lower && sgn(cross(h[(int)h.size() - 2], h.back(), pt)) <= 0)
            h.pop_back();
        h.push_back(pt);
    }
    h.pop_back();
    return h;
}

// squared diameter of a convex polygon in CCW order. O(n).
// Pitfalls: run convexHull first; hull should have no duplicate last point.
T diameter2(const vector<P>& p) {
    int n = (int)p.size();
    if (n <= 1) return 0;
    if (n == 2) return norm2(p[0] - p[1]);
    T ans = 0;
    int j = 1;
    for (int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        while (abs(cross(p[ni] - p[i], p[(j + 1) % n] - p[i])) >
               abs(cross(p[ni] - p[i], p[j] - p[i])))
            j = (j + 1) % n;
        ans = max(ans, norm2(p[i] - p[j]));
    }
    return ans;
}

// circle-line intersection. O(1).
// Pitfalls: a and b must be distinct; returns 0/1/2 points.
vector<P> circleLine(P c, T r, P a, P b) {
    P ab = b - a;
    P h = a + ab * (dot(c - a, ab) / norm2(ab));
    T d2 = norm2(h - c);
    if (sgn(d2 - r * r) > 0) return {};
    P dir = ab / norm(ab);
    if (sgn(d2 - r * r) == 0) return {h};
    T len = sqrt((double)max((T)0, r * r - d2));
    return {h - dir * len, h + dir * len};
}

// circle-circle intersection. O(1).
// Pitfalls: same center returns empty for both infinite and no intersections.
vector<P> circleCircle(P a, T r, P b, T R) {
    P ab = b - a;
    T d2 = norm2(ab), d = sqrt((double)d2);
    if (sgn(d) == 0) return {};
    T x = (d2 + r * r - R * R) / (2 * d);
    T h2 = r * r - x * x;
    if (sgn(h2) < 0) return {};
    P v = ab / d, p = a + v * x, q = perp(v);
    if (sgn(h2) == 0) return {p};
    T h = sqrt((double)max((T)0, h2));
    return {p - q * h, p + q * h};
}
