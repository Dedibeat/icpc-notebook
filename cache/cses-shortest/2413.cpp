#import<iostream>
main(){long m=1e9+7,n=2e6,d[n]={0,2,8},i=2;while(i++<n)d[i]=(6*d[i-1]-7*d[i-2])%m+m;while(std::cin>>i)if(d[0]++)printf("%d ",d[i]%m);}
