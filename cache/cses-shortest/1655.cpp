#import<bits/stdc++.h>
 
using namespace std;
int n,i,j,M,s[1<<18];
main()
{
    cin>>n;
    for(;i<n;i++)
        {cin>>j;
        s[i+1]=j^s[i];}
    for(j=1<<29;j;j/=2)
        {M+=j;
        set<int> S;
        for(i=n;i>=0&&!S.count(M-(M&s[i]));S.insert(M&s[i--]));
        M-=(i<0)*j;}
    cout<<M;
}