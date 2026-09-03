#include <bits/stdc++.h>
using namespace std;
#include "../sections/math/ntt.cpp"
#include "../sections/math/formal_power_series.cpp"

vector<ll> first(vector<ll>a,int n){a.resize(n);return a;}
int main(){mt19937_64 rng(43);for(int n=1;n<=100;++n)for(int it=0;it<30;++it){vector<ll>a(n);for(auto&x:a)x=rng()%NTT_MOD;a[0]=1;auto inv=fps_inv(a,n);auto product=first(conv_ntt(a,inv),n);assert(product[0]==1);for(int i=1;i<n;++i)assert(product[i]==0);auto logarithm=fps_log(a,n);assert(fps_exp(logarithm,n)==a);vector<ll>b(n);for(auto&x:b)x=rng()%NTT_MOD;b[0]=0;assert(fps_log(fps_exp(b,n),n)==b);}assert(fps_inv({},0).empty());}
