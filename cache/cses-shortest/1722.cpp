#import<iostream>
long n,a=1,b,c,d,i=a<<62,m=1e9+7;
main()
{
    for(std::cin>>n;i/=2;a=c%m,b=d%m)c=2*a*b+b*b,d=c+a*a+b*b,n&i?:d-=c=d-c;
    std::cout<<b;
}