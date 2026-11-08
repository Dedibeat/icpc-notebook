#include <bits/stdc++.h>
using namespace std;
#define I long
#define C(i) lower_bound(c, c+n, i) - c
#define F for(i=0; i<n; ++i)

I m = 1e9+7, a[1<<18], b[1<<18], c[1<<18], n, s, i;

void U(I i, I v){
	for(++i; i<=n; i+=i&-i) a[i] = (a[i] + v) % m;
}
I Q(I i){
	for(s=0; i>=1; i-=i&-i) s = (s + a[i]) % m;
	return s;
}

main(){
	cin >> n;
	F cin >> b[i], c[i] = b[i];
	sort(c, c+n);
	
	F U(C(b[i]), Q(C(b[i]))), U(C(b[i]), 1);
	cout << Q(n);
}