#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/bitmask_dp.cpp"

int main(){
    for(int mask=0;mask<256;++mask){auto s=submasks(mask);set<int>got(s.begin(),s.end());assert(s.back()==0);for(int x=0;x<256;++x)assert(got.count(x)==((x&mask)==x));}
    mt19937 rng(18);
    for(int n=0;n<=9;++n)for(int it=0;it<50;++it){
        vector<vector<long long>>c(n,vector<long long>(n));for(auto&r:c)for(auto&x:r)x=rng()%20;
        long long want=0;
        if(n){want=LLONG_MAX;vector<int>p;for(int v=1;v<n;++v)p.push_back(v);do{long long cur=0,at=0;for(int v:p)cur+=c[at][v],at=v;want=min(want,cur);}while(next_permutation(p.begin(),p.end()));}
        assert(tsp_path(c)==want);
    }
}
