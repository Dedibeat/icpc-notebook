// Default (gcd) AggQueue against a deque brute force.
// test_aggregate_queue_ordered.py checks noncommutative and non-idempotent ops.
#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/aggregate_queue.cpp"

long long brute(const deque<long long>& d) {
    long long g = 0;
    for (long long x : d) g = gcd(g, x);
    return g;
}

int main() {
    AggQueue q;
    assert(q.size() == 0 && q.query() == 0); // empty queue gives ID
    q.push(12), q.push(18);
    assert(q.query() == 6 && q.size() == 2); // printed example
    q.pop();
    assert(q.query() == 18 && q.size() == 1);
    q.pop();
    assert(q.size() == 0 && q.query() == 0); // drained, then reused below

    mt19937 rng(5);
    for (int round = 0; round < 300; round++) { // random mixes, same object reused
        deque<long long> d;
        int pushBias = 1 + rng() % 4, maxVal = round % 3 == 0 ? 6 : 1000;
        for (int it = 0; it < 400; it++) {
            if (d.empty() || (int)(rng() % (pushBias + 1)) != 0) {
                long long x = (long long)(rng() % (maxVal + 1)) * (1 + rng() % 12); // zeros included
                q.push(x), d.push_back(x);
            } else {
                q.pop(), d.pop_front();
            }
            assert(q.size() == (int)d.size() && q.query() == brute(d));
        }
        while (!d.empty()) q.pop(), d.pop_front(), assert(q.query() == brute(d));
        assert(q.size() == 0 && q.in.empty() && q.inAgg.size() == 1 && q.outAgg.size() == 1);
    }

    for (int it = 0; it < 300; it++) { // two pointers: longest window with gcd > 1
        int n = rng() % 60;
        vector<long long> a(n);
        for (auto& x : a) x = 1 + rng() % 30;
        AggQueue w;
        int best = 0;
        for (int l = 0, r = 0; r < n; r++) {
            w.push(a[r]);
            while (w.size() && w.query() == 1) w.pop(), l++;
            best = max(best, r - l + 1);
        }
        int want = 0;
        for (int l = 0; l < n; l++) {
            long long g = 0;
            for (int r = l; r < n; r++) if ((g = gcd(g, a[r])) > 1) want = max(want, r - l + 1); else break;
        }
        assert(best == want);
    }

    { // worst transfer pattern stays linear: fill, then alternate pop/push, then drain
        const int N = 1000000;
        AggQueue big;
        for (int i = 0; i < N; i++) big.push(6 * (i + 1));
        assert(big.query() == 6);
        for (int i = 0; i < N; i++) big.pop(), big.push(10 * (i + 1));
        assert(big.size() == N && big.query() == 10);
        big.push(15);
        assert(big.query() == 5);
        while (big.size() > 1) big.pop();
        assert(big.query() == 15);
    }
    puts("aggregate queue: ok");
}
