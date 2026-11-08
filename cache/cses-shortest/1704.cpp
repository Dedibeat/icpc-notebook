#import<bits/stdc++.h>
using namespace std;
#define I int
#define V vector<I>
V v;
#define O .push_back(
#define R .size()
V k['   '];
void d(I n, I p) {
	for (I u : k[n]) if (u ^ p) d(u,n);
	if (k[n] R == 1) v O n);
}
main() {
	I n,a,b;
	for (cin >> n;cin >> a >> b;) {
		k[a]O b);
		k[b]O a);
	}
	d(1,1);
	v O v[0]);
	cout << (b=v R/2) << ' ';
	for (a = 0; a<b; ++a) cout << v[a] << ' ' << v[b + a] << ' ';
}