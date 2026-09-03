#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/wavelet_tree.cpp"

int main(){WaveletTree empty;assert(empty.countLess(0,0,5)==0);WaveletTree extreme({LLONG_MIN,LLONG_MAX,LLONG_MAX});assert(extreme.countEqual(0,3,LLONG_MAX)==2);mt19937_64 rng(37);for(int n=1;n<=100;++n){vector<long long>a(n);for(auto&x:a)x=(long long)(rng()%31)-15;WaveletTree wt(a);for(int it=0;it<1000;++it){int l=rng()%n,r=l+1+rng()%(n-l);vector<long long>b(a.begin()+l,a.begin()+r);sort(b.begin(),b.end());int k=rng()%b.size();assert(wt.kth(l,r,k)==b[k]);long long x=(long long)(rng()%35)-17;assert(wt.countLess(l,r,x)==lower_bound(b.begin(),b.end(),x)-b.begin());assert(wt.countEqual(l,r,x)==count(b.begin(),b.end(),x));}}}
