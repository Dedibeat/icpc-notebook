#import<bits/stdc++.h>

using namespace std;

main()
{
    string s;cin>>s;
    int n=s.size(),l=0,r=0,i=1,z[n]={},p[n]={};
    for(;i<n;i++)
        {z[i]=max(0,min(r-i,z[i-l]));
        while(i+z[i]<n&&s[i+z[i]]==s[z[i]])
            z[i]++,
            l=i,
            r=i+z[i];
        p[i+z[i]-1]=max(p[i+z[i]-1],z[i]);}
    for(i=n-2;i;i--)
        p[i]=max(p[i],p[i+1]-1);
    for(i=0;i<n;i++)
        cout<<z[i]<<" ";
    cout<<"\n";
    for(i=0;i<n;i++)
        cout<<p[i]<<" ";
}