#include <bits/stdc++.h>
using namespace std;
#define F(i,s,t) for(int i=s;i<t;i++)
const int N=2e5;
int X[N],l[N],z[N<<1],P[N],C[N],T[N],O[N],D[N],I,n,q;
vector<int> G[N];
int K(int i,int p){
	P[i]=p;int s=1,c=-1,m=0;
	for(int j:G[i])if(j!=p){D[j]=D[i]+1;int ss=K(j,i);s+=ss;if(ss>m)c=j,m=ss;}
	return C[i]=c,s;
}
void Q(int i,int t){
	T[i]=t;O[i]=I;z[I+n]=l[i];I++;
	if(i!=t)l[i]=min(l[i],l[P[i]]);
	if(C[i]==-1)return;
	Q(C[i],t);
	for(int j:G[i])if(j!=P[i]&&j!=C[i])Q(j,j);
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>q;fill(l,l+n,n);
	int qt=0;
	F(i,0,n){int v;cin>>v;if(v)X[qt++]=i,l[i]=0;}
	F(i,0,n-1){int a,b;cin>>a>>b;--a;--b;G[a].push_back(b);G[b].push_back(a);}
	F(i,0,qt){int x=X[i];for(int y:G[x])if(l[y]==n)l[y]=l[x]+1,X[qt++]=y;}
	K(0,-1);Q(0,0);
	for(int i=n;i--;)z[i]=min(z[i<<1],z[i<<1|1]);
	while(q--){
		int a,b;cin>>a>>b;--a;--b;
		int ans=D[a]+D[b],r=n;
		while(T[a]!=T[b]){
			if(D[T[a]]<D[T[b]])swap(a,b);
			r=min(r,l[a]);a=P[T[a]];
		}
		if(D[a]<D[b])swap(a,b);
		ans-=D[b]*2;
		for(int s=O[b]+n,t=O[a]+n+1;s<t;s>>=1,t>>=1){
			if(s&1)r=min(r,z[s++]);
			if(t&1)r=min(r,z[--t]);
		}
		cout<<ans+(r<<1)<<'\n';
	}
}
