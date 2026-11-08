#import "bits/stdc++.h"
using namespace std;

#define i int
#define b push_back
const i M = 3e5;
i n, D, j, x, y, p[M], r[M];
vector<i> a[M], e[M], s;
 
void f(i o, i v, i l) {
	e[l].b(o);
	p[o] = v;
	for (i u: a[o])
		if (u-v) f(u, o, l+1);
}
 
i g(i u, i d) {
	if (!u || !d) return 1;
	if (r[u] + d > D) return 0;
	r[u] = d;
	return g(p[u], d - 1);
}

main() {
	cin >> n >> D;
	while (cin >> x >> y) 
		a[x].b(y), a[y].b(x);
	f(1, 0, 0); 
 
	for (j = n-1; j+1; j--) 
		for (i u: e[j]) 
			if (g(u, D)) 
				s.b(u);
			
	cout << size(s);
	for (i j: s) cout << ' ' << j;
}