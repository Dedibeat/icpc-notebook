// Exact integer geometry kit; no EPS or external geometry dependencies.
// Safe common bound: |coordinate| <= 10^15, polygon size <= 10^6.
// Wider inputs require every determinant/area sum to fit signed i128.
// Cast BEFORE subtraction/multiplication. Never multiply raw determinants.
// Polygon vertices stay in boundary order; only hull sorts a point SET.
using ll = long long;
__extension__ typedef __int128 i128;
struct IP {
    ll x, y;
    bool operator<(IP p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(IP p) const { return x == p.x && y == p.y; }
};

// Signed determinant and turn (-1 right, 0 straight, +1 left). O(1).
i128 cross_i(IP a, IP b, IP c) {
    return ((i128)b.x-a.x)*((i128)c.y-a.y) -
           ((i128)b.y-a.y)*((i128)c.x-a.x);
}
int ori_i(IP a, IP b, IP c) {
    i128 v = cross_i(a,b,c);
    return (v > 0) - (v < 0);
}

// Closed segment membership, including a==b. O(1).
bool onSeg_i(IP a, IP b, IP p) {
    return ori_i(a,b,p) == 0 &&
        min(a.x,b.x) <= p.x && p.x <= max(a.x,b.x) &&
        min(a.y,b.y) <= p.y && p.y <= max(a.y,b.y);
}

// Closed segments intersect? Touching/overlap/point segments count. O(1).
bool segInter_i(IP a, IP b, IP c, IP d) {
    int x = ori_i(a,b,c), y = ori_i(a,b,d);
    int z = ori_i(c,d,a), w = ori_i(c,d,b);
    if (x*y < 0 && z*w < 0) return true; // signs, not determinants
    return onSeg_i(a,b,c) || onSeg_i(a,b,d) ||
           onSeg_i(c,d,a) || onSeg_i(c,d,b);
}

// Strictly inside triangle, either orientation. Degenerate => false. O(1).
bool inTriStrict_i(IP a, IP b, IP c, IP q) {
    int x = ori_i(a,b,q), y = ori_i(b,c,q), z = ori_i(c,a,q);
    return x != 0 && x == y && y == z;
}

// Twice signed polygon area: CCW positive, CW negative. O(n), O(1) extra.
// Empty/point/segment => 0. Simple polygon required for geometric area.
i128 area2_i(const vector<IP>& p) {
    i128 sum = 0;
    for (int i = 0, n = p.size(); i < n; ++i) {
        IP a = p[i], b = p[(i+1)%n];
        sum += (i128)a.x*b.y - (i128)a.y*b.x;
    }
    return sum;
}

// Simple polygon, either orientation: 1 inside, 0 boundary, -1 outside.
// O(n), O(1) extra. Empty => -1; point/segment => boundary or outside.
// Repeated closing vertex is OK. Do NOT sort polygon vertices.
int inPolygon_i(const vector<IP>& p, IP q) {
    bool inside = false;
    for (int i = 0, n = p.size(); i < n; ++i) {
        IP a = p[i], b = p[(i+1)%n];
        if (onSeg_i(a,b,q)) return 0;
        if (a.y > b.y) swap(a,b);
        if (a.y <= q.y && q.y < b.y && ori_i(a,b,q) > 0)
            inside = !inside;
    }
    return inside ? 1 : -1;
}

// Strict CCW hull of a point SET, starting at smallest (x,y).
// O(n log n), O(n) extra. Drops duplicates/collinear interior points.
// Empty => {}; all collinear => endpoints; no repeated closing point.
vector<IP> hull_i(vector<IP> p) {
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    if (p.size() <= 2) return p;
    vector<IP> h;
    for (int pass = 0; pass < 2; ++pass) {
        int start = h.size();
        for (IP q : p) {
            while ((int)h.size() >= start+2 &&
                   ori_i(h[h.size()-2],h.back(),q) <= 0) h.pop_back();
            h.push_back(q);
        }
        h.pop_back();
        reverse(p.begin(),p.end());
    }
    return h;
}
// Example: auto h = hull_i({{0,0},{2,0},{0,2},{0,0}});
// area2_i(h)==4; inPolygon_i(h,{1,1})==0 (on the hypotenuse).
// Keep area as i128; do not narrow it just to print (use an i128 printer).
