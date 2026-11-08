#import <iostream>
long n,m,i,j,x,s,a,d['   '],b=1e9+7;
main() {
    for(;std::cin>>a;~i--?:m=a)
        for(x=j=s=0;j++<m;x=n)
            n=d[j],s+=d[j]=a&&a-j?0:i+2?(x+d[j]+d[j+1])%b:1;
    std::cout<<s%b;
}