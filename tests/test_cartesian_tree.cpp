#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/cartesian_tree.cpp"

int main(){mt19937 rng(35);for(int n=0;n<=100;++n)for(int it=0;it<100;++it){vector<long long>a(n);for(auto&x:a)x=(int)(rng()%11)-5;auto t=cartesian_tree(a);if(!n){assert(t.root==-1);continue;}vector<int>order;function<void(int)>dfs=[&](int v){if(v<0)return;dfs(t.left[v]);order.push_back(v);dfs(t.right[v]);};dfs(t.root);vector<int>want(n);iota(want.begin(),want.end(),0);assert(order==want);int roots=0;for(int v=0;v<n;++v){roots+=t.parent[v]==-1;if(t.left[v]>=0)assert(t.parent[t.left[v]]==v&&a[v]<=a[t.left[v]]);if(t.right[v]>=0)assert(t.parent[t.right[v]]==v&&a[v]<=a[t.right[v]]);}assert(roots==1);}}
