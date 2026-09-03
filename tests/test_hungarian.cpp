#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/hungarian.cpp"

int main(){
    assert(hungarian({}).first==0);mt19937 rng(31);
    for(int n=1;n<=7;++n)for(int m=n;m<=7;++m)for(int it=0;it<100;++it){
        vector<vector<long long>>a(n,vector<long long>(m));for(auto&r:a)for(auto&x:r)x=(int)(rng()%31)-15;
        auto [cost,match]=hungarian(a);vector<char>used(m);long long actual=0;for(int i=0;i<n;++i){assert(0<=match[i]&&match[i]<m&&!used[match[i]]);used[match[i]]=1;actual+=a[i][match[i]];}assert(actual==cost);
        vector<int>cols(m);iota(cols.begin(),cols.end(),0);long long want=LLONG_MAX;
        do{long long cur=0;for(int i=0;i<n;++i)cur+=a[i][cols[i]];want=min(want,cur);}while(next_permutation(cols.begin(),cols.end()));
        assert(cost==want);
    }
}
