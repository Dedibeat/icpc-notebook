#import<iostream>
using L=long;
#define S std::cin>>
#define F for(L T=0;T<3;++T)T
L B['   '][3],n,q,d,P,H,K,A;
void U(L p, L x){
	for(P=p;P<=n;P+=P&-P)
		F[B[P]]+=x*(!T?:T-1?p*p:p);
}
L Q(L p) {
	L R[3]={};
	for(P=p;P;P&=P-1)
		F[R]+=T[B[P]];
	return *R*++p*++p-R[1]*(2*p-1)+R[2];
}
main()
{
    for(S n>>d; q++<n; U(q,A-2*K+H),H=K,K=A)
	S A;
    for(;S q>>A>>K;)
	q-1 ? printf("%ld ",(Q(K)-Q(A-1))/2) : (U(A,1),U(K+1,A-K-2),U(K+2,K-A+1),0);
}