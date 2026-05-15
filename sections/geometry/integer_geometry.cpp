// Integer geometry orientation helper for large coordinates.
// Complexity: O(1).
// Pitfalls: use __int128 for cross when coordinates/products may overflow long long.
// Usage: int o = ori_i(a, b, c); // -1, 0, +1
using ll = long long;
__extension__ typedef __int128 i128;

struct IP {
    ll x, y;
};

i128 cross_i(IP a, IP b, IP c) {
    return (i128)(b.x - a.x) * (c.y - a.y) -
           (i128)(b.y - a.y) * (c.x - a.x);
}

int ori_i(IP a, IP b, IP c) {
    i128 v = cross_i(a, b, c);
    return (v > 0) - (v < 0);
}
