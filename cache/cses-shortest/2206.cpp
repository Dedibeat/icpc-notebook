#include<bits/stdc++.h>
#define S std::
#define M S min
#define I S cin>>t
int n,q,t,k,i,a,b,A[400000],B[400000];
void U(){
 i=k+n;
 a=t-i;b=t+i;
 while(i)
  A[i]=a,B[i]=b,
  a=M(a,A[i^1]),
  b=M(b,B[i^1]),
  i/=2;
}
int Q(int*T,int s,int e){
 t=2e9;
 while(s<e)
  t=s&1?M(t,T[s++]):t,
  t=e&1?M(t,T[e-1]):t,
  s/=2,e/=2;
 return t;
}
main(){
 S cin>>n>>q;
 for(;k<n;U(),k++)I;
 for(;q--;k--,t<2?I,U(),0:(S cout<<M(Q(A,n,n-~k)+k+n,Q(B,n+k,n+n)-k-n)<<' ',0))
  I>>k;
}
