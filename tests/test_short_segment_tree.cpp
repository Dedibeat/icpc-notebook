#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/short_segment_tree.cpp"
int main() {
    ShortST s, other(3);
    assert(s.query(0,0) == 0);
    other.set(1,42);
    mt19937 rng(42);
    for (int n = 0; n < 70; ++n) {
        vector<long long> a(n);
        for (auto& x : a) x = (long long)(rng()%2000000001)-1000000000;
        s.build(a);
        for (int it = 0; it < 200; ++it) {
            if (n && rng()%2) {
                int p = rng()%n;
                a[p] = (long long)(rng()%2000000001)-1000000000;
                s.set(p,a[p]); s.set(p,a[p]);
            }
            int l = rng()%(n+1), r = rng()%(n+1);
            if (l > r) swap(l,r);
            assert(s.query(l,r) == accumulate(a.begin()+l,a.begin()+r,0LL));
            assert(other.query(0,3) == 42);
        }
    }
    s.build({1000000000LL,1000000000LL,1000000000LL,1000000000LL});
    assert(s.query(0,4) == 4000000000LL);
    s.build({-5}); assert(s.query(0,1) == -5);
    s.build({}); assert(s.query(0,0) == 0);
}
