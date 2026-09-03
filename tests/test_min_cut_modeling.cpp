#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/dinic_2.cpp"
#include "../sections/graph/min_cut_modeling.cpp"

int main() {
    mt19937 rng(15);
    for(int n=0;n<=9;++n) for(int it=0;it<100;++it) {
        vector<long long>w(n);for(auto&x:w)x=(int)(rng()%15)-7;
        vector<pair<int,int>> imp;
        for(int u=0;u<n;++u)for(int v=0;v<n;++v)if(u!=v && rng()%12==0)imp.push_back({u,v});
        long long want=LLONG_MIN; int bestMask=0;
        for(int mask=0;mask<(1<<n);++mask){
            bool ok=true;for(auto[u,v]:imp)if(mask>>u&1)ok&=mask>>v&1;
            if(!ok) continue;
            long long val=0;for(int v=0;v<n;++v)if(mask>>v&1)val+=w[v];
            if(val>want)want=val,bestMask=mask;
        }
        auto got=max_weight_closure(w,imp);
        assert(got.value==want);
        vector<char> chosen(n);for(int v:got.chosen)chosen[v]=1;
        long long value=0;for(int v=0;v<n;++v)if(chosen[v])value+=w[v];
        for(auto[u,v]:imp)if(chosen[u])assert(chosen[v]);
        assert(value==got.value);
        (void)bestMask;
    }
}
