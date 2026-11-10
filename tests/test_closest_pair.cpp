#include <bits/stdc++.h>
using namespace std;

#include "../sections/geometry/geometry_base.cpp"
#include "../sections/geometry/convex_hull.cpp"
#include "../sections/geometry/closest_pair.cpp"

bool close(T a, T b) {
    return fabsl(a - b) < 1e-9;
}

T brute(vector<P> p) {
    T ans = 1e100;
    for (int i = 0; i < (int)p.size(); i++)
        for (int j = i + 1; j < (int)p.size(); j++)
            ans = min(ans, norm2(p[i] - p[j]));
    return ans;
}

int main() {
    vector<P> p = {{0, 0}, {3, 4}, {1, 1}, {-2, 5}};
    assert(close(closestPair(p).first, 2));

    p = {{0, 0}, {1, 1}, {0, 0}, {5, 5}};
    assert(close(closestPair(p).first, 0));
    assert(closestPair(vector<P>(100000,{0,0})).first == 0);
    p.resize(100000);
    for (int i = 0; i < (int)p.size(); ++i) p[i] = {0, i * 1e-20L};
    auto d = closestPair(p).first;
    assert(d > 0 && fabsl(d / 1e-40L - 1) < 1e-10L);

    mt19937 rng(2);
    for (int tc = 0; tc < 500; tc++) {
        int n = 2 + rng() % 40;
        p.resize(n);
        for (P& q : p) {
            q.x = (int)(rng() % 101) - 50;
            q.y = (int)(rng() % 101) - 50;
        }
        assert(close(closestPair(p).first, brute(p)));
    }
}
