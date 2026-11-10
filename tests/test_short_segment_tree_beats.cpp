#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/short_segment_tree_beats.cpp"
#include "../sections/data_structures/segment_tree_beats.cpp"

int main() {
    Beats empty({});
    empty.chmin(0,0,7);
    assert(empty.sum(0,0)==0 && empty.max(0,0)==LLONG_MIN);

    Beats ties({7,4,7,4});
    ties.chmin(0,4,4); // cap equals second maximum, so counts must be rebuilt
    ties.chmin(1,4,-1);
    assert(ties.sum(0,4)==1 && ties.max(1,4)==-1);
    Beats wide({LLONG_MAX});
    wide.chmin(0,1,LLONG_MIN+1);
    assert(wide.sum(0,1)==LLONG_MIN+1);

    mt19937 rng(452);
    for (int n=1; n<=70; ++n) {
        vector<long long> a(n);
        for (auto& x : a) x=(int)(rng()%11)-5 + 2'000'000'000LL;
        Beats st(a);
        SegTreeBeats full(a);
        for (int i=0; i<1200; ++i) {
            int l=rng()%(n+1), r=rng()%(n+1);
            if (l>r) swap(l,r);
            if (i%3==0) {
                long long cap=(int)(rng()%21)-10+(i<15 ? 2'000'000'000LL : 0);
                st.chmin(l,r,cap);
                full.chmin(l,r,cap);
                for (int j=l; j<r; ++j) a[j]=min(a[j],cap);
            } else {
                auto s=accumulate(a.begin()+l,a.begin()+r,0LL);
                assert(st.sum(l,r)==s && full.sum(l,r)==s);
                if (l<r) {
                    auto mx=*max_element(a.begin()+l,a.begin()+r);
                    assert(st.max(l,r)==mx && full.max(l,r)==mx);
                }
            }
        }
    }
}
