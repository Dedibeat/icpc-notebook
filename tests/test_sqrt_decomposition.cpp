#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/sqrt_decomposition.cpp"

int main() {
    mt19937 rng(7);
    for (int n = 0; n <= 60; ++n) {
        vector<long long> a(n);
        for (auto& x : a) x = (int)(rng()%21)-10;
        SqrtDecomp s(a);
        for (int it = 0; it < 500; ++it) {
            int l = rng() % (n+1), r = rng() % (n+1); if (l > r) swap(l,r);
            if (rng()&1) {
                long long x = (int)(rng()%21)-10;
                s.update(l,r,x); for (int i=l;i<r;++i) a[i]+=x;
            } else {
                long long want = accumulate(a.begin()+l,a.begin()+r,0LL);
                assert(s.query(l,r)==want);
            }
        }
    }
}
