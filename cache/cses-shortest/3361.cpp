#import<bits/stdc++.h>
using namespace std;
double n,q,w,a['   '],b['   '],l,r=1e9;
int i;
main(){
    for(cin>>n;i<n;i++)cin>>a[i];
    for(i=0;i<n;i++)cin>>b[i];
    while(r-l>1e-6){
        double m=(l+r)/2,d=0,y=-1e9,f=0,k=-1e9;
        for(i=0;i<n;i++){d+=a[i]-m;if(y<d)y=d,q=i;}
        for(i=0;i<n;i++){f+=b[i]-m;if(k<f)k=f,w=i;}
        if(y+k>=0)l=m;
        else r=m;
    }
    cout << q+1 << " " << w+1;
}