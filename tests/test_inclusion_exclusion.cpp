#include <bits/stdc++.h>
using namespace std;
#include "../sections/math/inclusion_exclusion.cpp"

int main(){mt19937 rng(36);for(int k=0;k<=8;++k)for(int it=0;it<300;++it){int universe=20;vector<int>sets(k);for(int&i:sets)i=rng()&((1<<universe)-1);vector<long long>inter(1<<k);for(int mask=1;mask<(1<<k);++mask){int bits=(1<<universe)-1;for(int i=0;i<k;++i)if(mask>>i&1)bits&=sets[i];inter[mask]=__builtin_popcount((unsigned)bits);}int uni=0;for(int x:sets)uni|=x;assert(union_size_ie(inter)==__builtin_popcount((unsigned)uni));}
    const long long MOD=1000000007;for(int n=0;n<=8;++n)for(int k=0;k<=6;++k){long long brute=0,total=1;for(int i=0;i<n;++i)total*=k;for(long long mask=0;mask<total;++mask){long long x=mask;int used=0;for(int i=0;i<n;++i)used|=1<<(x%max(1,k)),x/=max(1,k);if(__builtin_popcount((unsigned)used)==k)++brute;}if(k==0)brute=n==0;assert(surjections_ie(n,k,MOD)==brute%MOD);}}
