#include <iostream>
long long b,B,c,C,s,n,a,A;int main(){std::cin>>n>>a>>A;while(n-->1){std::cin>>c>>C;c-=a,C-=A;s+=c*B-C*b;B=C,b=c;}std::cout<<llabs(s);}