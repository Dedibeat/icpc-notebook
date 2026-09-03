#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/link_cut_tree.cpp"

vector<int> path(const vector<set<int>>&g,int s,int t){vector<int>p(g.size(),-1);queue<int>q;q.push(s);p[s]=s;while(!q.empty()){int v=q.front();q.pop();for(int u:g[v])if(p[u]<0)p[u]=v,q.push(u);}if(p[t]<0)return{};vector<int>r;for(int v=t;;v=p[v]){r.push_back(v);if(v==s)break;}return r;}
int main(){mt19937 rng(45);for(int n=1;n<=20;++n){vector<long long>value(n);for(auto&x:value)x=(int)(rng()%21)-10;LinkCut lct(value);vector<set<int>>g(n);for(int it=0;it<10000;++it){int u=rng()%n,v=rng()%n,type=rng()%5;auto p=path(g,u,v);if(type==0&&u!=v&&!p.size()){assert(lct.link(u,v));g[u].insert(v);g[v].insert(u);}else if(type==1&&u!=v&&g[u].count(v)){assert(lct.cut(u,v));g[u].erase(v);g[v].erase(u);}else if(type==2){long long x=(int)(rng()%41)-20;value[u]=x;lct.setValue(u,x);}else if(type==3){assert(lct.connected(u,v)==(!p.empty()));}else if(!p.empty()){long long want=0;for(int x:p)want+=value[x];assert(lct.pathQuery(u,v)==want);}}}}
