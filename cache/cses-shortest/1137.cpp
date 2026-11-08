#include <bits/stdc++.h>
using namespace std;
#define I int64_t
#define F(z) for(I j=0; j<z; ++j)
 
set<I> g[1<<18];
I L[1<<18], R[1<<18], s, n, q, x, y, a[1<<18], b[1<<18];


I U(I i, I v){
	for(; i<=n; i+=i&-i) a[i] += v;
}
I Q(I i){
	for(s=0; i; i-=i&-i) s += a[i];
	return s;
}
I D(I u, I p){
	L[u] = ++s;
	U(s, b[u]);
	for(I v : g[u]) v - p ? D(v, u) : 0;
	R[u] = s;
}

main(){
	cin >> n >> q;
	F(n) cin >> b[j+1];
	F(n-1)
		cin >> x >> y, g[x].insert(y), g[y].insert(x);

	D(1, 0);

	F(q){
		cin >> s >> x;
		if(s-2) cin >> y, U(L[x], y - b[x]), b[x] = y;
		else cout << Q(R[x]) - Q(L[x]-1) << ' ';
	}
}