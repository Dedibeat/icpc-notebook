#include <bits/stdc++.h>
#define t(x) p[i][x]
#define F for (i=

using namespace std;

int n,q,p[18]['	  '],e['	  '],a,b,i,j,s;
set<int> c['	  '];
 
void f(int i,int r)
{
	for (int d: c[i]) if (d^r) e[d]=e[i]+1,f(d,p[0][d]=i);
}
 
main()
{
	cin.tie(0);
	cin>>n>>q;
	F 0;++i<n;)
	{
		cin>>a>>b;
		c[a].insert(b);
		c[b].insert(a);
	}
	f(1,0);
	F 0;i<17;++i) for (j=1;j<=n;++j) p[i+1][j]=t(t(j));
	while (q--)
	{
		cin>>a>>b;
		if (e[b]<e[a]) swap(a,b);
		s=0;
		F 18;i-->0;) if (e[b]-e[a]>>i) b=t(b),s+=1<<i;
		F 18;i-->0;) if (t(a)^t(b)) a=t(a),b=t(b),s+=2<<i;
		cout<<s+2*(a!=b)<<' ';
	}
}

