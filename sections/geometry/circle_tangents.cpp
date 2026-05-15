// Tangent points between two circles. Depends on geometry base.
// Source: KACTL CircleTangents style.
// Complexity: O(1).
// Pitfalls: use r2 = 0 for tangents from point c2 to circle c1; negate r2 for internal tangents.
// Usage: auto t = circleTangents(c, r, p, 0); // pairs {on circle, p}
vector<pair<P, P>> circleTangents(P c1, T r1, P c2, T r2) {
    P d = c2 - c1;
    T dr = r1 - r2, d2 = norm2(d), h2 = d2 - dr * dr;
    if (sgn(d2) == 0 || sgn(h2) < 0) return {};
    vector<pair<P, P>> out;
    for (T sign : {-1.0L, 1.0L}) {
        P v = (d * dr + perp(d) * sqrt((double)max((T)0, h2)) * sign) / d2;
        out.push_back({c1 + v * r1, c2 + v * r2});
    }
    if (sgn(h2) == 0) out.pop_back();
    return out;
}
