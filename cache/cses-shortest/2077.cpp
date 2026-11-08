#import<bits/stdc++.h>
 
using namespace std;
 
#define I int
#define X [x]
#define s .insert(
#define O ['   '],
 
set<I> v O W;
I d O F O k O g,t;
 
void f(I x, I e)
{
	k X =1;
	F X =d X;
	for(I u : v X)
        if(u!=e)
            {if(k[u])
                g=d[u];
            else
                d[u]=d X +1,
                f(u,x),
                g=F[u];
            F X =min(F X ,g);}
	if(F X >=d X -1 && (e>1 || e && t))
		W s e);
    t+=e<2;
}
 
main()
{
	I x,y;cin>>x>>y;
	while(cin>>x>>y)
		v X s y),
		v[y] s x);
	f(1,0);
	cout<<W.size()<<"\n";
	for(I x : W)
		cout<<x<<" ";
}