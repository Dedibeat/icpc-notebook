#include <bits/stdc++.h>
using namespace std;
#define I int64_t
#define F(z) for(auto &i : z)
 
I c[1<<18], n, q, s, j;
 
I U(I i, I v){
	for(; i<=n && i; i+=i&-i) c[i] += v;
}
I Q(I i){
	for(s=0; i; i-=i&-i) s += c[i];
	return s;
}
 
main(){
	cin >> n >> q;
	map<I, I> L;
	I a[n], d[q]; F(a) cin >> i;
 
	array<I, 3> b[q];
	F(b) cin >> i[1] >> i[0], i[2] = s++;
	sort(b, b+q);
 
	F(b){
		while(j<i[0]) U(L[a[j]], -1), U(L[a[j]]=j+1, 1), ++j;
		d[i[2]] = Q(i[0]) - Q(i[1]-1);
	}
	F(d) cout << i << ' ';
}