#import<iostream>
#define _ [o]
#define C std::
#define J ['   '],
using I = int;
I R=1,z J l J r J p J k J n,a,b,o=1;
C string s;
void U(I o){
	z _ =z[l _ ]+z[r _ ]+1;
}
I M(I o,I b){
	I t = o+b;
	if(o*b)
	p _ >p[b] ?
	   	r _ =M(r[t = o],b) :
		l[b]=M(o,l[t = b]), U(t);
	return t;
}
void S(I o,I& a,I& b,I k){
	if(o)
 		if(z[l _ ]<k)a=o,S(r _ ,r _ ,b,k-z[l _ ]-1),U(a);
		else b=o,S(l _ ,a,l _ ,k),U(b);
	else a=b=0;
}
void O(I o){
	if(o)
		O(l _ ), C cout<<s[k _ ], O(r _ );
}
main(){
	C cin>>n>>s>>s;
	C fill(z + 1,z+'   ',1);
	for(;o++-n;)
	   	k _=o-1,p _=rand(), R=M(R,o);
	while(C cin>>o>>n)
		S(a = R,R,a,o-1), S(b = a,a,b,n-o+1), R=M(R,M(b,a));
	O(R);
}
