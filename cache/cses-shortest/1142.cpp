#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,a[maxn],st[maxn];
long long ans=0;
int main(){
    cin>>n;
    for(int i=1,sn=1;i<=n+1;i++){
      if(i<=n)cin>>a[i];
      while(a[i]<a[st[sn-1]]){
        sn--;
        ans=max(ans,(i-st[sn-1]-1LL)*a[st[sn]]);
      }
      st[sn++]=i;
    }
    cout<<ans;
}