#include <bits/stdc++.h>
using namespace std;
using I = int;

vector<I> g[1 << 19], d(1 << 19);

I n, x, y, i = 1;

void D(I u, I p = 0, I c = 0){
	d[u] = max(d[u], c++);
	if(c > y) x = u, y = c;
	for(I v : g[u]) if(v - p) D(v, u, c);
}

main(){
	cin >> n;

	for(; i<n; ++i)
		cin >> x >> y,
		g[x].push_back(y),
		g[y].push_back(x);

	y = -1;
	D(1);
	D(x);
	D(x);
	for(i=1; i<=n;) cout << d[i++] << ' ';
}