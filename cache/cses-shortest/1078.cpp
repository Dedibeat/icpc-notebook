#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
const ll N=1<<21,M=1000000007;
ll n,m,f[N],S[N],x,y,i,j;
ll P(ll a,ll b){
    a%=M;
    ll R=1;
    while(b){
        if(b%2)R=(R*a)%M;
        a=(a*a)%M;
        b/=2;
    }
    return R;
}
ll F(ll n,ll k){
    return (f[n]*P(f[n-k]*f[k],M-2))%M;
}
vector<pii>V;
int main()
{f[0]=1;
    for(i=1;i<N;i++)f[i]=(f[i-1]*i)%M;
    cin>>n>>m;
    V={{n,n}};
    for(i=0;i<m;i++){
        cin>>x>>y;V.push_back({x,y});
    }
    sort(V.begin(),V.end());
    for(i=0;i<=m;i++){
        pii &C=V[i];
        S[i]=F(C.x+C.y-2,C.x-1);
        for(j=0;j<i;j++){
            pii &P=V[j];
            if(P.x<=C.x&&P.y<=C.y)S[i]=((S[i]-F(C.x+C.y-P.x-P.y,C.x-P.x)*S[j])%M+M)%M;
        }
    }
    cout<<S[m];
}
