// Closest pair of points. Depends on geometry base.
// Source: standard divide-and-conquer closest pair.
// Complexity: O(n log n).
// Pitfalls: returns squared distance; duplicate points give 0; needs n >= 2.
// Usage: auto [d2, pr] = closestPair(points);
pair<T, pair<P, P>> closestPair(vector<P> p) {
    assert((int)p.size() >= 2);
    sort(p.begin(), p.end(), [](P a, P b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    vector<P> tmp(p.size());
    pair<T, pair<P, P>> ans = {norm2(p[0] - p[1]), {p[0], p[1]}};

    auto upd = [&](P a, P b) {
        T d = norm2(a - b);
        if (d < ans.first) ans = {d, {a, b}};
    };

    function<void(int, int)> solve = [&](int l, int r) {
        if (r - l <= 3) {
            for (int i = l; i < r; i++)
                for (int j = i + 1; j < r; j++) upd(p[i], p[j]);
            sort(p.begin() + l, p.begin() + r, [](P a, P b) { return a.y < b.y; });
            return;
        }
        int m = (l + r) / 2;
        T mx = p[m].x;
        solve(l, m);
        solve(m, r);
        merge(p.begin() + l, p.begin() + m, p.begin() + m, p.begin() + r,
              tmp.begin(), [](P a, P b) { return a.y < b.y; });
        copy(tmp.begin(), tmp.begin() + (r - l), p.begin() + l);

        int sz = 0;
        T d = sqrt((double)ans.first);
        for (int i = l; i < r; i++) if (fabsl(p[i].x - mx) <= d + EPS) {
            for (int j = sz - 1; j >= 0 && p[i].y - tmp[j].y <= d + EPS; j--)
                upd(p[i], tmp[j]);
            tmp[sz++] = p[i];
        }
    };
    solve(0, (int)p.size());
    return ans;
}
