#include<bits/stdc++.h>
using namespace std;

set<int> g[200005];
vector<int> v;


void dfs(int x){
	while(!g[x].empty()){
		auto u = *g[x].begin();
		g[u].erase(x);
		g[x].erase(u);
		dfs(u);
	}
	v.push_back(x);
}

int main(){
	int n, m, a, b; cin >> n >> m;
	for(int i = 1; i<=m; i++){
		cin >> a >> b;
		g[a].insert(b);
		g[b].insert(a);
	}
	for(int i = 1; i<=n; i++)
		if (g[i].size()&1)
			return cout << "IMPOSSIBLE", 0;
	dfs(1);
	if (v.size()!=m+1)
		return cout << "IMPOSSIBLE", 0;
	for(auto x : v) cout << x << " ";
}
