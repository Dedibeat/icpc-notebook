/*
GEOMETRY CHECKLIST
1. int or floating?
2. Need EPS?
3. Coordinates up to 1e9 => integer cross may need __int128.
4. Segment intersection: endpoint? overlap? collinear?
5. Convex hull: keep or remove collinear points?
6. Polygon vertices clockwise or counterclockwise?
7. Area is signed; use abs(area2)/2.
8. For angle/sqrt, clamp values if needed.
9. For circles, handle tangent and same-center cases.
*/

// Shared floating-point geometry base.
// Source: KACTL Point style, simplified for notebook use.
// Complexity: each primitive is O(1).
// Pitfalls: operator< is exact for sort/set; geometric equality uses EPS.
// Usage: copy this before other floating geometry snippets.
using T = long double;
const T EPS = 1e-12;

int sgn(T x) { return (x > EPS) - (x < -EPS); }

struct P {
    T x, y;
    bool operator<(P p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator==(P p) const {
        return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
    }
    P operator+(P p) const { return {x + p.x, y + p.y}; }
    P operator-(P p) const { return {x - p.x, y - p.y}; }
    P operator*(T k) const { return {x * k, y * k}; }
    P operator/(T k) const { return {x / k, y / k}; }
};

T dot(P a, P b) { return a.x * b.x + a.y * b.y; }
T cross(P a, P b) { return a.x * b.y - a.y * b.x; }
T cross(P a, P b, P c) { return cross(b - a, c - a); }
T norm2(P a) { return dot(a, a); }
T norm(P a) { return sqrt((double)norm2(a)); }
P perp(P a) { return {-a.y, a.x}; }

int ori(P a, P b, P c) { return sgn(cross(a, b, c)); }

bool onSegment(P a, P b, P p) {
    return ori(a, b, p) == 0 && sgn(dot(p - a, p - b)) <= 0;
}
