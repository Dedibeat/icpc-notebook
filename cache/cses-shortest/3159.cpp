#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int sum,x[N];
bitset<N*N/2>f[N];
queue<int>l,r;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&x[i]),sum+=x[i];
	f[0][0]=1;int now=sum/2;
	for(int i=1;i<=n;i++)f[i]=f[i-1]|(f[i-1]<<x[i]);
	if(sum%2==1||!f[n][sum/2])return printf("-1\n"),0;
	for(int i=n;i>=1;i--)
	{
		if(now>=x[i]&&f[i-1][now-x[i]])now-=x[i],l.push(x[i]);
		else r.push(x[i]);
	}
	while(!l.empty()&&!r.empty())
	{
		int x=l.front(),y=r.front();
		l.pop(),r.pop();
		if(x>y)l.push(x-y);
		else r.push(y-x);
		printf("%d %d\n",x,y);
	}
	return 0;
}