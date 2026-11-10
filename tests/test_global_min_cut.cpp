#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/global_min_cut.cpp"

int main() {
    assert(globalMinCut({}).second.empty());
    assert(globalMinCut({{0}}).first==0);
    assert(globalMinCut({{0,LLONG_MAX},{LLONG_MAX,0}}).first==LLONG_MAX);
    vector<vector<long long>> triangle(3,vector<long long>(3,2'000'000'000LL));
    for (int i=0; i<3; ++i) triangle[i][i]=0;
    assert(globalMinCut(triangle).first==4'000'000'000LL);

    mt19937 rng(57);
    for (int n=2; n<=9; ++n) for (int it=0; it<150; ++it) {
        vector<vector<long long>> a(n,vector<long long>(n));
        for (int i=0; i<n; ++i) for (int j=0; j<i; ++j)
            a[i][j]=a[j][i]=(rng()%3 ? 0 : rng()%6 * 1'000'000'000LL);
        auto cut = [&](int mask) {
            long long w=0;
            for (int i=0; i<n; ++i) for (int j=0; j<i; ++j)
                if ((mask>>i&1)!=(mask>>j&1)) w+=a[i][j];
            return w;
        };
        long long want=LLONG_MAX;
        for (int mask=1; mask<(1<<n)-1; ++mask) want=min(want,cut(mask));
        auto [weight,side]=globalMinCut(a);
        int mask=0;
        for (int u : side) mask|=1<<u;
        assert(0<mask && mask<(1<<n)-1 && weight==want && cut(mask)==want);
    }
}
