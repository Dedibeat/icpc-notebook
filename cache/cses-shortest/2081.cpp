#import "bits/stdc++.h"
using namespace std;
using I=long;
#define F for(
#define P .push_back(
#define S .size()
I a,b,K,H;
deque<I> t,x[1<<18];
void D(I u,I p)	
{
	deque<I> k;
	k P 1);
	k P 0);
	F I o:x[u])
	if(o-p)
	{
		D(o,u);
		swap(k,k S<t S?t:k);
		I Z=k S;
		F a=0;a<t S-1;a++)
		H-a<Z?b+=(t[a]-t[a+1])*(k[H-a<0?0:H-a]-(K-a<Z?k[K-a<0?0:K-a]:0)):0;
		F ;a--;)
		k[a]+=t[a];
	}
	swap(k,t);
	t.push_front(t[0]);
}
main()
{
	F cin>>a>>H>>K;cin>>a>>b;x[a] P b))x[b] P a);
	D(K++,b=0);
	cout<<b;
}
