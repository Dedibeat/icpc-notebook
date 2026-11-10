// In-process stress test: no scripts or files, about 1e5 tests/s.
// Paste the solution as fast(), write an obviously correct brute(), edit the generator.
// Build: g++ -O2 -fsanitize=address,undefined stress.cpp && ./a.out
// Fixed seed: a failing test reproduces on every run. fast() runs many times,
// so a global it forgets to reset fails here exactly as on a multi-test judge.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(1);
ll rnd(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }

ll fast(vector<ll> a) {  // example: max nonempty subarray sum (Kadane)
    ll best = a[0], cur = 0;
    for (ll x : a) cur = max(cur + x, x), best = max(best, cur);
    return best;
}
ll brute(vector<ll> a) {
    ll best = LLONG_MIN;
    for (int l = 0; l < (int)a.size(); l++)
        for (ll r = l, s = 0; r < (ll)a.size(); r++) s += a[r], best = max(best, s);
    return best;
}
int main() {
    for (int it = 0; it < 100000; it++) {
        int n = rnd(1, 6);  // tiny n and values: readable test, many ties
        vector<ll> a(n);
        for (ll &x : a) x = rnd(-5, 5);
        ll x = fast(a), y = brute(a);
        if (x != y) {
            cout << "test " << it << ": n = " << n << "\n";
            for (ll v : a) cout << v << ' ';
            cout << "\nfast " << x << ", brute " << y << "\n";
            return 1;
        }
    }
    cout << "OK\n";
}
