#include <bits/stdc++.h>
using namespace std;
#include "../sections/math/lucas_theorem.cpp"

long long bruteC(int n,int k,int p){if(k<0||k>n)return 0;vector<long long>d(k+1);d[0]=1;for(int i=1;i<=n;++i)for(int j=min(i,k);j;--j)d[j]=(d[j]+d[j-1])%p;return d[k];}
int main(){for(int p:{2,3,5,7,11,17,29}){Lucas l(p);for(int n=0;n<=250;++n)for(int k=0;k<=n+1;++k)assert(l.C(n,k)==bruteC(n,k,p));assert(l.C(2LL*p,p)==2%p);}}
