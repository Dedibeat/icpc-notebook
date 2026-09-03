#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/rerooting.cpp"

int main() {
    mt19937 rng(14);
    for(int n=1;n<=100;++n) {
        vector<vector<int>> g(n);
        for(int v=1;v<n;++v){int p=rng()%v;g[v].push_back(p);g[p].push_back(v);}
        auto got=Rerooting(g).solve();
        for(int s=0;s<n;++s){
            vector<int>d(n,-1);queue<int>q;q.push(s);d[s]=0;
            while(!q.empty()){int v=q.front();q.pop();for(int u:g[v])if(d[u]<0)d[u]=d[v]+1,q.push(u);}
            assert(got[s].size==n);
            assert(got[s].sum==accumulate(d.begin(),d.end(),0LL));
        }
    }
}
