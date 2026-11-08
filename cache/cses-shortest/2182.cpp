#import<iostream>
#define h std::cin>>a
using l=long;
l a,b,s=1,p=1,d=1,m=1e9+7,r;
l w(l x,l y){r=y?w(x,y/2):1;return r*r%m*(y&1?x:1)%m;}
main(l c)
{
    for(h;h>>b;d=d*b%~-m)p=w(w(a,b++*b/2),d)*w(p,b)%m,c=c*b%m,s=s*w(a-1,m-2)%m*~-w(a,b)%m;
    printf("%d %d %d",c,s,p);
}