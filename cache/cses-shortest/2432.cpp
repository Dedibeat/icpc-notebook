#import"bits/stdc++.h"
using namespace std;
int n,i,j,a[60],b[60],R[60],C[60];
string g[60];
#define F for(
main(){
    F cin>>n;i<n;)cin>>a[i++];
    F ;j<n;)cin>>b[j++];
    F array<int,2>v[n];i--;j=n){
        F ;j--;g[i]+=46)v[j]={C[j]-b[j],j};
        sort(v,v+n);
        F auto[_,j]:v)if(R[i]<a[i]&&_)g[i][j]=88,R[i]++,C[j]++;
    }
    F ;j--;)if(R[j]^a[j]|C[j]^b[j])return cout<<-1,0;
    F auto i:g)cout<<i<<' ';
}