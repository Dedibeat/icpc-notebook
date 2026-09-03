#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/aliens_trick.cpp"

int main(){mt19937 rng(42);for(int n=1;n<=100;++n)for(int it=0;it<100;++it){vector<long long>a(n);for(auto&x:a)x=(int)(rng()%101)-50;sort(a.begin(),a.end());for(int k=0;k<=n;++k){auto solve=[&](long long lambda){long long cost=0;int count=0;for(long long x:a)if(x+lambda<=0)cost+=x+lambda,++count;return pair<long long,int>{cost,count};};long long want=accumulate(a.begin(),a.begin()+k,0LL);assert(lagrangian_exact_k(k,-100,100,solve)==want);assert(aliens_exact_k(k,-100,100,solve)==want);}}}
