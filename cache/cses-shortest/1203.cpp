#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define IOS cin.tie(0)->sync_with_stdio(0)
const int mx=1e5+1;
const ll o=1e9+87;
vector<pair<int, ll>> l[mx], k[mx];
ll t1[mx], t2[mx];
int c1[mx], c2[mx];

void f(int s, vector<pair<int, ll>> j[], ll t[], int c[]) {
    priority_queue<pair<ll, int>> q;
    q.push({0, s});
    t[s]=0;
    c[s]=1;
    while (!q.empty()) {
        auto [d, u]=q.top();
        q.pop();
        d=-d;
        if (d > t[u]) continue;
        for (auto [v, w]:j[u]) {
            if (d + w < t[v]) {
                t[v]=d + w;
                c[v]=c[u];
                q.push({-t[v], v});
            } else if (d + w == t[v]) c[v]=(c[v] + c[u])%o;
        }
    }
}

int main() {
	IOS;
    int n, m, a, b;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        ll c;
        cin>>a>>b>>c;
        l[a].push_back({b, c});
        k[b].push_back({a, c});
    }
    fill(t1, t1+mx, 1e18);
    fill(t2, t2+mx, 1e18);
    f(1, l, t1, c1);
    f(n, k, t2, c2);
    vector<int> v;
    for(int i=1;i<=n;i++)
        if((ll)c1[i]*c2[i]%o==c1[n])
            if(t1[i]+t2[i]==t1[n])
                v.push_back(i);
    cout<<v.size()<<'\n';
    for(int i:v) cout<<i<<' ';
    return 0;
}