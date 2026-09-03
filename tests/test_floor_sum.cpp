#include <bits/stdc++.h>
using namespace std;
#include "../sections/math/floor_sum.cpp"

int main(){
    mt19937_64 rng(20);
    for(int it=0;it<200000;++it){long long n=rng()%30,m=1+rng()%30,a=rng()%100,b=rng()%100;__int128 want=0;for(int i=0;i<n;++i)want+=((__int128)a*i+b)/m;assert(floor_sum(n,m,a,b)==want);}
    assert(floor_sum(0,1,0,0)==0);
}
