#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using vll=vector<ll>;
#define SZ (1<<20)
struct line{
    ll a,b;
    ll operator()(ll x){
        return a*x+b;
    }
};
vector<line> seg;
void update(ll i,ll l, ll r, line f){
    ll mid=(l+r)/2;
    if(f(mid)<seg[i](mid))swap(seg[i],f);
    if(l==r-1)return;
    if(seg[i](l)<f(l)){
        update(2*i+1,mid,r,f);
    }
    else{
        update(2*i,l,mid,f);
    }
}
ll query(ll i){
    ll ans=1e18;
    for(ll j=i+SZ;j>0;j/=2){
        ans=min(ans,seg[j](i));
    }
    return ans;
}
int main(){
    ll n,x;cin>>n>>x;
    line l;
    l.a=x;
    l.b=0;
    seg.assign(2*SZ,l);
    vll dp(n),s(n),f(n);
    for(ll&i:s)cin>>i;
    for(ll&i:f)cin>>i;
    for(ll i=0;i<n;i++){ 
        dp[i]=query(s[i]);
        line l;
        l.a=f[i];
        l.b=dp[i];
        update(1,0,SZ,l);
    }
    cout << dp[n-1];
}