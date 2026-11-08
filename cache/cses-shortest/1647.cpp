#import<iostream>
using namespace std;
int n,i,a,b,m[2*'   '];
main()
{
	for(cin>>n>>a;i<n;)cin>>m[n+i++];
	for(;i--;)m[i]=min(m[2*i],m[2*i+1]);
	for(n--;cin>>a>>b;printf("%d ",i))for(a+=n,b+=n,i=1e9;a<=b;a/=2,b/=2)i=a&1?min(m[a++],i):i,b&1?:i=min(m[b--],i);
}
