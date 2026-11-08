#import "bits/stdc++.h"
using namespace std;const int N=1e7;int a[N],b[N],c[N],n,i;main(){cin>>n;for(i=0;i<n;i++)cin>>a[i];for(i=0;i<n;i++)cin>>b[i],c[i]=i+1;if(n<3)cout<<"IMPOSSIBLE";else while(1){random_shuffle(c,c+n);int o=1;for(i=0;i<n;i++)o&=c[i]!=b[i]&c[i]!=a[i];if(o){for(i=0;i<n;i++)cout<<i[c]<<" ";break;}}}
