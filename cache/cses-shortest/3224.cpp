#import<bits/stdc++.h>

using namespace std;

int n,k,i,x['   '];

main()
{
    cin>>n>>k;
    map<int,int> f;
    set<pair<int,int>> S;
    while(i<n)
        {cin>>x[i];
        S.insert({--f[x[i]],x[i++]});
        if(i>=k)
            cout<<S.begin()->second<<" ",
            S.erase({f[x[i-k]]++,x[i-k]});}
}