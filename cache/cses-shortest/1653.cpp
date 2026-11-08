#include <bits/stdc++.h>
using namespace std;int64_t n,m,k,a,t,p,x,w[25],d[1<<21],f=1e18;int main(){for(cin>>n>>x,x++,k=n<<n,d[0]=-f;m<k;m++,p*=2)t=m/n,a=d[t]+f,m%n?0:p=1,d[t|p]=min(d[t|p],d[t]+(t?cin:cin>>w[m%n],w[m%n])+((a%x+w[m%n]<x)?0:x-a%x)),(m-k+1?cout:cout<<(a+x-1)/x);}
