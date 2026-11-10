#include <bits/stdc++.h>
using namespace std;
#include "../sections/math/NT_essentials.cpp"
#include "../sections/math/CRT.cpp"

int main() {
    assert(inv_any(-1,7)==6 && inv_any(-2,6)==-1);
    assert(modpow(5,0,1)==0 && modpow(-2,3,7)==6);
    assert((crt(LLONG_MIN,2,LLONG_MAX,3)==pair<long long,long long>{4,6}));
    for (int a=-8; a<=8; ++a) for (int b=-8; b<=8; ++b)
        for (int m=1; m<=8; ++m) for (int n=1; n<=8; ++n) {
            int lim=lcm(m,n), want=-1;
            for (int x=0; x<lim; ++x) if ((x-a)%m==0 && (x-b)%n==0) {
                want=x;
                break;
            }
            auto [x,mod]=crt(a,m,b,n);
            assert(x==want && mod==(want<0 ? -1 : lim));
        }
}
