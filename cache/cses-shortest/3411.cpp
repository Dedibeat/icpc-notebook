#include<bits/stdc++.h>
using namespace std;
__int128_t sx,sy,r,i;
long x['   '],y['   '],n;
int main(){
    for(cin>>n;i<n;i++)cin>>x[i]>>y[i];
    sort(x,x+n);sort(y,y+n);
    for(i=0;i<n;i++)r+=i*x[i]-sx,sx+=x[i],r+=i*y[i]-sy,sy+=y[i];
    if(r>1e9) cout << (long)(r/1e9) << (long)(r%(long)1e9);
    else cout << (long)r;
}