#include <bits/stdc++.h>
using namespace std;
#include "../sections/geometry/max_plus_convolution.cpp"

vector<ll> brute(const vector<ll>& a,const vector<ll>& b) {
    if(a.empty()||b.empty()) return {};
    vector<ll> c(a.size()+b.size()-1,LLONG_MIN);
    for(int i=0;i<(int)a.size();++i) for(int j=0;j<(int)b.size();++j)
        c[i+j]=max(c[i+j],a[i]+b[j]);
    return c;
}
bool concave(const vector<ll>& a) {
    for(int i=2;i<(int)a.size();++i)
        if((i128)a[i]-a[i-1]>(i128)a[i-1]-a[i-2]) return false;
    return true;
}
vector<ll> makeConcave(mt19937_64& rng,int n) {
    vector<ll> a(n); if(!n) return a;
    a[0]=(ll)(rng()%41)-20;
    ll slope=(ll)(rng()%21)-10;
    for(int i=1;i<n;++i) { a[i]=a[i-1]+slope; slope-=(ll)(rng()%6); }
    return a;
}
int main() {
    assert(maxPlusConcave({}, {1}).empty());
    assert((maxPlusConcave({5}, {-2})==vector<ll>{3}));
   assert((maxPlusConcave({0,3,5}, {0,4,5})==vector<ll>{0,4,7,9,10}));
    assert((maxPlusConcave({0,0}, {0,0})==vector<ll>{0,0,0})); // ties
    assert((maxPlusConcave({LLONG_MIN,LLONG_MIN+5}, {0})==
            vector<ll>{LLONG_MIN,LLONG_MIN+5}));
    assert((maxPlusConcave({LLONG_MAX-5,LLONG_MAX}, {0})==
            vector<ll>{LLONG_MAX-5,LLONG_MAX}));
   assert((maxPlusConcave({-5,-2,-2,-3}, {4,4,1})==
           brute(vector<ll>{-5,-2,-2,-3},vector<ll>{4,4,1})));
    assert(!concave({0,1,3}));
    assert(!concave({3,3,4})); // invalid inputs are excluded by the assertion
    mt19937_64 rng(19);
    for(int it=0;it<3000;++it) {
        auto a=makeConcave(rng,1+rng()%12),b=makeConcave(rng,1+rng()%12);
        assert(concave(a)&&concave(b));
        assert(maxPlusConcave(a,b)==brute(a,b));
    }
}
