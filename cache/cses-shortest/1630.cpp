#import<bits/stdc++.h>
using namespace std;
long n,x,i,t,a['   '];
main(){
    for(cin>>n;cin>>a[i++]>>x;t+=x);
    for(sort(a,a+n);--i+1;t-=(n-i)*a[i]);
    cout<<t;
}
