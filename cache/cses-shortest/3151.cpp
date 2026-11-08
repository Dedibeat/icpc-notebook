#import <bits/stdc++.h>
using namespace std;
int i,m,x;
 
main()
{
    cin>>x;
    pair<int,int> a[x];
    for(;cin>>x;i++)
        a[i]={x,i};
    
    for(sort(a,a+i);i--;)
    m<a[i].second-i&&(m=a[i].second-i);
    cout<< m;
}
