#include <bits/stdc++.h>
using namespace std;

using ll=long long;

array<ll,2> dirs[] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

void solve(){
	ll n,m; cin >> n >> m;
	
	vector<string> g1(n), g2(n, string(m, ' '));
	for(auto &s : g1) cin >> s;
	
	auto set = [&](auto &&set, ll i, ll j, char ls) {
		if(i<0 || j<0 || i>=n || j>=m) return;
		if(ls == g1[i][j]) return;
		if(g2[i][j] != ' ') {
			if(ls == g2[i][j]) {
				cout << "IMPOSSIBLE\n";
				exit(0);
			}
			return;
		}
		g2[i][j] = 'A'^'B'^'C'^g1[i][j]^ls;
		for(auto [dx,dy] : dirs) set(set, i+dx, j+dy, g2[i][j]);
	};
	
	for(ll i=0;i<n-1;i++) for(ll j=0;j<m-1;j++) {
		ll oc = 0;
		for(ll k=0;k<2;k++) for(ll l=0;l<2;l++) oc |= 1<<(g1[i+k][j+l]-'A');
		if(oc != 7) continue;
		if(g1[i][j] == g1[i+1][j])     set(set, i,j, g1[i+1][j+1]);
		if(g1[i][j] == g1[i][j+1])     set(set, i,j, g1[i+1][j+1]);
		if(g1[i+1][j] == g1[i+1][j+1]) set(set, i+1,j+1, g1[i][j]);
		if(g1[i][j+1] == g1[i+1][j+1]) set(set, i+1,j+1, g1[i][j]);
	}
	
	for(ll i=0;i<n;i++) for(ll j=0;j<n;j++) if(g2[i][j] == ' ') {
		char ch = g1[i][j]+1;
		if(ch == 'D') ch = 'A';
		set(set, i,j, ch);
	}
	
	for(auto &s : g2) cout << s << '\n';
}

int main() { cin.sync_with_stdio(0); cin.tie(0);
	
	
	ll t=1; //cin >> t;
	while(t--) solve();
}
