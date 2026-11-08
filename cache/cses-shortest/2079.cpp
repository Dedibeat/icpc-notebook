#import "iostream"
using namespace std;
#define I int
I n,a,b;
basic_string<I>g['   '];
void D(I u,I p)
{
	I k=2;
	for(I o:g[u])
	o^p?D(o,u),(k+=a)>n==b?b=u:0:0;
	a=k;
}
main()
{
	for(cin>>n;cin>>a>>b;g[a]+=b)g[b]+=a;
	D(b=1,0);
	cout<<b;
}
