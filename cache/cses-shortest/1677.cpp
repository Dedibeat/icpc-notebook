#import<bits/stdc++.h>
using namespace std;
int p['   '],n,m,R,a,b,e['   '];
pair<int,int>r['   '];set c(r,r);
#define F (r[R]);for(0;
#define P )e[R]=f(a)^f(b)?p[a]=b,n--:n;F
#define H --;)cin>>a>>b,r[R]={a<b?a:b,a<b?b:a},c.
int f(int& x){return x=p[x]?f(p[x]):x;}
main()
{
    cin>>n>>m>>R;
    F m H insert
    F R H erase
    F auto[a,b]:c P
    tie(a,b)=r[++R],a;P
    --R;)cout<<e[R-1]<<' ';
}