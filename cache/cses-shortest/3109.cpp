#include<bits/stdc++.h>
using namespace std;
using ll=long long;
main(){
    ll n,m,k;cin>>n>>m>>k;
    vector<ll>a(n);
    for(auto&x:a)cin>>x;
    sort(a.begin(),a.end());
    priority_queue<array<ll,4>>q;
    q.push({-accumulate(a.begin(),a.begin()+m,0ll),0,-1,m});
    while(k--){
        auto[t,i,h,j]=q.top();q.pop();
        cout<<-t<<' ';
        if(j<n)q.push({t-a[j]+a[j-1],h+1,j-1,j+1});
        if(h>i)q.push({t-a[h]+a[h-1],i,h-1,j});
    }
}
