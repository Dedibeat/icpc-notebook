#include <iostream>
using L=long long;int main(){L n,l=0,r=1e18;std::cin>>n;while(r-l>1){L m=l+r>>1,c=0,p=1;for(;p<=m;p*=10)c+=(m/p+8)/10*p+(m/p%10==1)*(m%p+1);(c>n?r:l)=m;}std::cout<<l;}