#import <bits/stdc++.h>
using namespace std;
using I = int;
map<I, I> g['   '];
I n, a, b;
bitset<8<<14> s, t;
 
#define F ;for (a = 0; a++ < n;)
#define A [a] 
I d(I a) {
	I c = t A = s[0] = 1;
	for (auto [a, _]: g A)
		t A ? c : c += d(a);
	return c;
}
 
main() {
	for (cin >> n >> a; 
			cin >> a >> b; 
			g[b] A)
		g A [b]
	
	F t A ? s : s |= s << d(a)
	F cout << s A;
}