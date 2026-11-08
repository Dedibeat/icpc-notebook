#include<bits/stdc++.h>
using namespace std;
int n,m,k,i,j,s;
main(){
    cin>>n>>m>>k;
    int a[n],b[m];
    for(int &i:a) cin>>i;
    for(int &i:b) cin>>i;
    sort(a,a+n);
	sort(b,b+m);
	for(i=j=0;i<n&&j<m;)
		(abs(a[i]-b[j])<=k)?++s,++i,++j:(a[i]>b[j])?++j:++i;
	cout << s;
} 
