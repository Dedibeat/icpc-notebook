#import<bits/stdc++.h>
using namespace std;
int a,b,i;
vector<int>g['  '];
struct S {
	int v,p,o,t;
};
queue<S>q;
main() {
	for(cin>>a>>b; cin>>a>>b;g[b].push_back(a))
	    g[a].push_back(b);
	for(; ++i<'  '; q.push({i,0,i,1}));
	for(; q.size(); q.pop()) {
		auto [v,p,o,t]=q.front();
		for(int j:g[v])
			if(j-p) {
				if(j==o)
					return cout<<t,0;
				q.push({j,v,o,t+1});
			}
	}
	cout<<-1;
}