#import<bits/stdc++.h>
using namespace std;
set<array<long,3>> e;
long p['   '],r,a,b,x;
int F(long&x){return x=x[p]>0?F(x[p]):x;}
main()
{
    for(cin>>a;cin>>a>>b>>x;)e.insert({-x,a,b});
    for(auto[x,a,b]:e)
        r-=x*--p[F(a)]*~-p[F(b)],
        p[b]+=p[a],
        p[a]=b;
    cout<<r;
}