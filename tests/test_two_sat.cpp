#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/two_sat.cpp"

int lit(int var, bool neg) { return neg ? ~var : var; }

int main() {
    // basic: (x0 or x1), (!x0 or x1), (!x1 or !x1) => x1 forced... unsat check
    {
        TwoSat ts(2);
        ts.either(0, 1);
        ts.either(~0, 1);
        ts.either(~1, ~1);
        assert(!ts.solve()); // x1 must be true and false
    }
    {
        TwoSat ts(2);
        ts.either(0, 1);
        ts.either(~0, 1);
        assert(ts.solve());
        assert(ts.values[1] == 1 || ts.values[0] == 1);
        // verify clauses hold
        auto v = ts.values;
        assert((v[0] || v[1]) && (!v[0] || v[1]));
    }
    {
        TwoSat ts(3);
        ts.setValue(0);
        ts.setValue(~1);
        ts.either(~0, 2);
        assert(ts.solve());
        assert(ts.values[0] == 1 && ts.values[1] == 0 && ts.values[2] == 1);
    }
    {
        TwoSat ts(4);
        ts.atMostOne({0, 1, 2, 3});
        ts.setValue(2);
        assert(ts.solve());
        assert(ts.values[2] == 1 && !ts.values[0] && !ts.values[1] && !ts.values[3]);
    }
    // randomized vs brute force
    mt19937 rng(2024);
    for (int it = 0; it < 300; it++) {
        int n = 1 + rng() % 6, m = 1 + rng() % 12;
        vector<array<int, 4>> clauses; // var1, neg1, var2, neg2
        TwoSat ts(n);
        for (int i = 0; i < m; i++) {
            int a = rng() % n, b = rng() % n;
            int na = rng() % 2, nb = rng() % 2;
            clauses.push_back({a, na, b, nb});
            ts.either(lit(a, na), lit(b, nb));
        }
        bool bruteSat = false;
        for (int mask = 0; mask < (1 << n) && !bruteSat; mask++) {
            bool ok = true;
            for (auto& c : clauses) {
                bool va = ((mask >> c[0]) & 1) ^ c[1];
                bool vb = ((mask >> c[2]) & 1) ^ c[3];
                if (!va && !vb) { ok = false; break; }
            }
            bruteSat = ok;
        }
        bool got = ts.solve();
        assert(got == bruteSat);
        if (got) { // returned assignment must satisfy all clauses
            for (auto& c : clauses) {
                bool va = ts.values[c[0]] ^ c[1];
                bool vb = ts.values[c[2]] ^ c[3];
                assert(va || vb);
            }
        }
    }
    return 0;
}
