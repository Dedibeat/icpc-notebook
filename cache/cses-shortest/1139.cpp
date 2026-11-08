#include <bits/stdc++.h>
using namespace std;
#define F for(
#define I .insert
#define Z int
#define G .size()
Z r['   '], n, a, b, i;
set<Z> g['   '], c['   '];
 
void D(Z u){
	F Z v : g[u]) {
		g[v].erase(u);
		D(v);
		swap(c[u], c[c[u] G < c[v] G ? v : u]);
		F Z x : c[v]) c[u] I(x);
	}
	r[u] = c[u] G;
}
 
main(){
	cin >> n;
	F ;i++<n;) cin >> a, c[i] I(a);
 
	F ;cin>>a>>b;) g[a]I(b), g[b]I(a);
 
	D(1);
 
	F ;--i;) cout << r[n-i+1] << ' ';
}
