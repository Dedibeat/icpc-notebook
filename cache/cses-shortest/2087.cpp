#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3005;
int n,k,a[N],d[N][N];
ll s[N],v[N],w[N][N],f[N][N];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),s[i]=s[i-1]+a[i],v[i]=v[i-1]+1ll*a[i]*i;
	for(int i=1;i<=n;i++) for(int j=i,m=i;j<=n;j++){
		while(s[m]*2-s[i-1]<s[j]) m++;
		w[i][j]=(s[m]*2-s[i-1]-s[j])*m+v[i-1]+v[j]-v[m]*2;
	}
	memset(f,0x3f,sizeof f);f[0][0]=0;
	for(int i=1;i<=k;i++) for(int j=d[n+1][i]=n;j;j--)
		for(int t=d[j][i-1];t<=d[j+1][i];t++) if(f[t][i-1]+w[t+1][j]<f[j][i])
			f[j][i]=f[t][i-1]+w[t+1][j],d[j][i]=t;
	printf("%lld\n",f[n][k]);
	return 0;
}
