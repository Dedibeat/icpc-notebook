#import <iostream>
using namespace std;
#define c(i) (a[i] > a[i + 1])
#define R for(i = 0; i++ < n;)
int a['   '], r['   '], n, m, u, v, s, x, y, i;
int t() {
	u = r[x], v = r[y];
	if (u > v) swap(u, v);
	return c(u) + c(u-1) + c(v) + (v > u + 1 && c(v-1));
}
main() {
	cin >> n >> m;
	R cin >> r[i], a[r[i]] = i;
	R s += c(i);
	while (m--)
		cin >> x >> y, s -= t(), swap(a[u], a[v]), swap(r[x], r[y]), s += t(), cout << s << ' ';
}