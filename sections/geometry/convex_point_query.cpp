// Point in convex polygon in O(log n). Depends on geometry base.
// Source: KACTL PointInsideHull style.
// Complexity: O(log n) per query after CCW convex hull is built.
// Pitfalls: polygon must be CCW and have no duplicate last point; strict excludes boundary.
// Usage: bool ok = inConvex(poly, q, false);
bool inConvex(const vector<P>& p, P q, bool strict = false) {
    int n = (int)p.size();
    if (n == 0) return false;
    if (n == 1) return !strict && p[0] == q;
    if (n == 2) return !strict && onSegment(p[0], p[1], q);
    int a = ori(p[0], p[1], q), b = ori(p[0], p[n - 1], q);
    if (a < 0 || b > 0) return false;
    if (strict && (a == 0 || b == 0)) return false;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (ori(p[0], p[m], q) >= 0) l = m;
        else r = m;
    }
    int o = ori(p[l], p[(l + 1) % n], q);
    return strict ? o > 0 : o >= 0;
}
