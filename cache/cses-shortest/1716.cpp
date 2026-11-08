#import<iostream>
long m=1e9+7,n,k,a=1,b=1;
main()
{
    for(std::cin>>n>>k;--n;b=b*n%m)a=a*(n+k)%m;
    for(n=m-2;n;n/=2)a=n&1?a*b%m:a,b=b*b%m;
    std::cout<<a;
}
