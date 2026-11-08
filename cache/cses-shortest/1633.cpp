#import<iostream>
int m=1e9+7,n,d['   '],i,j;
main()
{
    std::cin>>n;
    for(*d=1;++i<=n;)for(j=0;++j<7&&i>=j;)(d[i]+=d[i-j])%=m;
    std::cout<<d[n];
}