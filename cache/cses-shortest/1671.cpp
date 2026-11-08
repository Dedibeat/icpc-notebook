#import<bits/stdc++.h>
using namespace std;
using l=long;
l n,a,c,h;
main()
{
    cin>>n>>c;deque<l>d(n,1e17);
    set<tuple<l,l>>q,o['   '];
    for(l b;cin>>a>>b>>c;a=1)o[a].emplace(c,b);
    for(d[0]=0;n--;q.erase(tie(h,a)=*begin(q)))for(auto [r,p]:o[a])
        if(l& z=d[p-1];z>h+r)q.erase({z,p}),q.emplace(z=h+r,p);
    for(l x:d)cout<<x<<' ';
}
