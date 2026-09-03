#include <bits/stdc++.h>
using namespace std;
#include "../sections/math/lagrange_interpolation.cpp"

long long eval(const vector<long long>&a,long long x){long long r=0,p=1;x=(x%LAGRANGE_MOD+LAGRANGE_MOD)%LAGRANGE_MOD;for(long long c:a)r=(r+c*p)%LAGRANGE_MOD,p=p*x%LAGRANGE_MOD;return r;}
int main(){
    mt19937_64 rng(21);
    for(int n=1;n<=40;++n)for(int it=0;it<100;++it){vector<long long>a(n),y(n);for(auto&c:a)c=rng()%LAGRANGE_MOD;for(int i=0;i<n;++i)y[i]=eval(a,i);for(long long x:{-7LL,0LL,(long long)n-1,(long long)n,1000000000000LL})assert(lagrangeConsecutive(y,x)==eval(a,x));}
}
