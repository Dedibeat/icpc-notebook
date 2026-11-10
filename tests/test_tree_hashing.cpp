#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/tree_hashing.cpp"

vector<vector<int>> tree(int n,mt19937&rng){vector<vector<int>>g(n);for(int v=1;v<n;++v){int p=rng()%v;g[v].push_back(p);g[p].push_back(v);}return g;}

vector<vector<int>> permuteTree(const vector<vector<int>>&g,const vector<int>&p){int n=g.size();vector<vector<int>>h(n);for(int v=0;v<n;++v)for(int u:g[v])if(v<u)h[p[v]].push_back(p[u]),h[p[u]].push_back(p[v]);return h;}
bool bruteIso(const vector<vector<int>>&a,const vector<vector<int>>&b){int n=a.size();vector<vector<char>>x(n,vector<char>(n)),y=x;for(int v=0;v<n;++v)for(int u:a[v])x[v][u]=1;for(int v=0;v<n;++v)for(int u:b[v])y[v][u]=1;vector<int>p(n);iota(p.begin(),p.end(),0);do{bool ok=true;for(int i=0;i<n;++i)for(int j=0;j<n;++j)ok&=x[i][j]==y[p[i]][p[j]];if(ok)return true;}while(next_permutation(p.begin(),p.end()));return false;}
int main() {
    mt19937 rng(32);
    TreeCanon canon;
    assert(canon.unrooted({{1},{0}}) != canon.unrooted({{1},{0,2},{1}}));
    for (int n=1; n<=7; ++n) for (int it=0; it<80; ++it) {
        auto a=tree(n,rng), b=tree(n,rng);
        vector<int> p(n);
        iota(p.begin(),p.end(),0);
        shuffle(p.begin(),p.end(),rng);
        assert(canon.unrooted(a)==canon.unrooted(permuteTree(a,p)));
        assert((canon.unrooted(a)==canon.unrooted(b))==bruteIso(a,b));
    }
}
