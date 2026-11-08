#include <bits/stdc++.h>
using namespace std;
using I = long;
#define F(z) for(i=1; i<=z; ++i)

const I N = 5e5;

vector<I> g[N];
I S[N], E[N], a[N], b[N], T = 1, i, n, q, x, y;

void U(I i, I v){
	for(; i<=N; i+=i&-i) b[i] += v;
}
I Q(I i){
	for(T=0; i; i-=i&-i) T += b[i];
	return T;
}

void D(I u, I p){
	S[u] = T++;
	for(I v : g[u]) if(v - p) D(v, u);
	E[u] = T++;
}

main(){
	cin >> n >> q;

	F(n) cin >> a[i];

	F(n-1)
		cin >> x >> y,
		g[x].push_back(y),
		g[y].push_back(x);

	D(1, 1);

	F(n)
		U(S[i], a[i]),
		U(E[i], -a[i]);

	F(q){
		cin >> T >> x;
		if(T-2) cin >> y, U(S[x], y -= a[x]), U(E[x], -y), a[x] += y;
		else cout << Q(S[x]) << '\n';
	}
}