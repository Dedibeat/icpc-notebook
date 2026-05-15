#include <bits/stdc++.h>
using namespace std;

#include "../sections/geometry/geometry_base.cpp"
#include "../sections/geometry/convex_hull.cpp"
#include "../sections/geometry/minimum_enclosing_circle.cpp"

bool close(T a, T b) {
    return fabsl(a - b) < 1e-8;
}

void check_contains(const vector<P>& p, P c, T r) {
    for (P q : p) assert(norm(c - q) <= r + 1e-8);
}

pair<P, T> brute_mec(const vector<P>& p) {
    if (p.empty()) return {{0, 0}, 0};
    pair<P, T> best = {{0, 0}, 1e100};
    auto try_circle = [&](P c, T r) {
        for (P q : p) if (norm(c - q) > r + 1e-8) return;
        if (r < best.second) best = {c, r};
    };
    for (P a : p) try_circle(a, 0);
    for (int i = 0; i < (int)p.size(); i++)
        for (int j = i + 1; j < (int)p.size(); j++) {
            P c = (p[i] + p[j]) / 2;
            try_circle(c, norm(c - p[i]));
        }
    for (int i = 0; i < (int)p.size(); i++)
        for (int j = i + 1; j < (int)p.size(); j++)
            for (int k = j + 1; k < (int)p.size(); k++)
                if (fabsl(cross(p[j] - p[i], p[k] - p[i])) > 1e-12) {
                    P c = circumcenter(p[i], p[j], p[k]);
                    try_circle(c, norm(c - p[i]));
                }
    return best;
}

int main() {
    {
        vector<P> p;
        auto [c, r] = minimum_enclosing_circle(p);
        assert(close(c.x, 0) && close(c.y, 0) && close(r, 0));
    }
    {
        vector<P> p = {{2, -3}};
        auto [c, r] = minimum_enclosing_circle(p);
        assert(close(c.x, 2) && close(c.y, -3) && close(r, 0));
    }
    {
        vector<P> p = {{0, 0}, {2, 0}, {1, 0}, {2, 0}};
        auto [c, r] = minimum_enclosing_circle(p);
        check_contains(p, c, r);
        assert(close(c.x, 1) && close(c.y, 0) && close(r, 1));
    }
    {
        vector<P> p = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {0, 0}};
        auto [c, r] = minimum_enclosing_circle(p);
        check_contains(p, c, r);
        assert(close(c.x, 0) && close(c.y, 0) && close(r, 1));
    }
    {
        vector<P> p = {{0, 0}, {4, 0}, {0, 3}};
        auto [c, r] = minimum_enclosing_circle(p);
        check_contains(p, c, r);
        assert(close(c.x, 2) && close(c.y, 1.5) && close(r, 2.5));
    }
    mt19937 rng(1);
    for (int tc = 0; tc < 300; tc++) {
        int n = 1 + rng() % 8;
        vector<P> p(n);
        for (P& q : p) {
            q.x = (int)(rng() % 21) - 10;
            q.y = (int)(rng() % 21) - 10;
        }
        auto got = minimum_enclosing_circle(p);
        auto want = brute_mec(p);
        check_contains(p, got.first, got.second);
        assert(fabsl(got.second - want.second) < 1e-7);
    }
}
