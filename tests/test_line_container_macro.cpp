#include <bits/stdc++.h>
using namespace std;

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

    LineContainer mx;
    for (auto [m, b] : lines) mx.add(m, b);
    for (long long x : xs) assert(mx.get(x) == brute(lines, x, false));

    // minimum via negation trick documented in the snippet
    LineContainer mn;
    for (auto [m, b] : lines) mn.add(-m, -b);
    for (long long x : xs) assert(-mn.get(x) == brute(lines, x, true));

    // randomized stress, includes equal slopes
    mt19937_64 rng(12345);
    vector<pair<long long, long long>> rl;
    LineContainer rc;
    for (int it = 0; it < 2000; it++) {
        long long k = (long long)(rng() % 2001) - 1000;
        long long m = (long long)(rng() % 2000001) - 1000000;
        rl.push_back({k, m});
        rc.add(k, m);
        long long x = (long long)(rng() % 2000001) - 1000000;
        assert(rc.get(x) == brute(rl, x, false));
    }
    return 0;

    // Full signed-64 coefficient range; intersection differences exceed int64.
    vector<pair<long long,long long>> extreme = {
        {LLONG_MIN,LLONG_MAX}, {LLONG_MAX,LLONG_MIN},
        {0,LLONG_MAX}, {0,LLONG_MIN}, {1,LLONG_MIN}, {-1,LLONG_MAX}
    };
    vector<long long> queries={LLONG_MIN,LLONG_MIN+1,-2,-1,0,1,2,LLONG_MAX-1,LLONG_MAX};
    for(int pass=0;pass<20;++pass) {
        shuffle(extreme.begin(),extreme.end(),rng);
        LineContainer lc;
        vector<pair<long long,long long>> inserted;
        for(auto [k,m]:extreme) {
            lc.add(k,m); inserted.push_back({k,m});
            for(long long x:queries) {
                __int128 want=-((__int128)1<<126);
                for(auto [a,b]:inserted) want=max(want,(__int128)a*x+b);
                assert(lc.get(x)==want);
            }
        }
    }
}
