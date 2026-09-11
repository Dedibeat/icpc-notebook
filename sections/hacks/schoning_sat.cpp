// Randomized 3-SAT witness search; nullopt = NOT FOUND, never an UNSAT proof.
// Literal +(v+1) means x[v], -(v+1) means !x[v]; clauses have 1..3 literals.
// Time O(restarts*n*m), memory O(n). Each restart makes <=3n random flips.
// For satisfiable inputs, expected O((4/3)^n) restarts; budget may be too small.
// Usage: schoning(2, {{1,2},{-1,2}}, 100, rng); empty formula is satisfiable.
#include "common.hpp"

optional<vector<int>> schoning(int n, const vector<vector<int>>& clauses,
                               int restarts, mt19937_64& rng) {
    assert(n >= 0 && restarts >= 0);
    for (const auto& c : clauses) {
        assert(c.size() <= 3);
        if (c.empty()) return nullopt;
        for (int lit : c) assert(lit != 0 && abs((ll)lit) <= n);
    }
    if (clauses.empty()) return vector<int>(n);
    while (restarts--) {
        vector<int> a(n);
        for (int& x : a) x = pick(rng, 0, 1);
        for (ll step = 0; step <= 3LL*n; ++step) {
            int bad = -1;
            for (int i = 0; i < (int)clauses.size(); ++i) {
                bool ok = false;
                for (int lit : clauses[i])
                    ok |= a[abs(lit)-1] == (lit > 0);
                if (!ok) { bad = i; break; }
            }
            if (bad == -1) return a;
            if (step == 3LL*n) break;
            const auto& c = clauses[bad];
            int lit = c[pick(rng, 0, c.size()-1)];
            a[abs(lit)-1] ^= 1;
        }
    }
    return nullopt;
}
