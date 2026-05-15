// Minimum enclosing circle for points in the plane.
// Source: KACTL MinEnclosingCircle, adapted to the shared geometry P.
// Complexity: expected O(n).
// Pitfalls: randomized order; copy geometry base first; use EPS when checking containment.
// Usage: auto [c, r] = minimum_enclosing_circle(points);
P circumcenter(P a, P b, P c) {
    b = b - a, c = c - a;
    T d = 2 * cross(b, c);
    return a + P{
        (c.y * (b.x * b.x + b.y * b.y) - b.y * (c.x * c.x + c.y * c.y)) / d,
        (b.x * (c.x * c.x + c.y * c.y) - c.x * (b.x * b.x + b.y * b.y)) / d
    };
}

pair<P, T> minimum_enclosing_circle(vector<P> p) {
    if (p.empty()) return {{0, 0}, 0};
    shuffle(p.begin(), p.end(), mt19937(chrono::steady_clock::now().time_since_epoch().count()));
    P c = p[0];
    T r = 0, mult = 1 + 1e-10;
    for (int i = 0; i < (int)p.size(); i++) if (norm(c - p[i]) > r * mult) {
        c = p[i], r = 0;
        for (int j = 0; j < i; j++) if (norm(c - p[j]) > r * mult) {
            c = (p[i] + p[j]) / 2;
            r = norm(c - p[i]);
            for (int k = 0; k < j; k++) if (norm(c - p[k]) > r * mult) {
                c = circumcenter(p[i], p[j], p[k]);
                r = norm(c - p[i]);
            }
        }
    }
    return {c, r};
}
