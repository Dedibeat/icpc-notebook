#include <bits/stdc++.h>
using namespace std;

#define int long long
#include "../sections/data_structures/line_container.cpp"
#undef int

long long brute(const vector<pair<long long, long long>>& lines, long long x, bool want_min) {
    long long ans = want_min ? LLONG_MAX : LLONG_MIN;
    for (auto [m, b] : lines) {
        long long y = m * x + b;
        if (want_min) ans = min(ans, y);
        else ans = max(ans, y);
    }
    return ans;
}

int main() {
    vector<pair<long long, long long>> lines = {
        {1000000000LL, 1000000000LL},
        {-1000000000LL, 5},
        {2, -7},
        {2, 3}
    };
    vector<long long> xs = {-1000000000LL, -3, 0, 4, 1000000000LL};

    minimum = true;
    LineContainer mn;
    for (auto [m, b] : lines) mn.add(m, b);
    for (long long x : xs) assert(mn.get(x) == brute(lines, x, true));

    minimum = false;
    LineContainer mx;
    for (auto [m, b] : lines) mx.add(m, b);
    for (long long x : xs) assert(mx.get(x) == brute(lines, x, false));
}
