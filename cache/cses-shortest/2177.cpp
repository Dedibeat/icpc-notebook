#include <bits/stdc++.h>
using namespace std;
#define g push_back
#define y int

const y M=2e5;
y t[M],l[M],c=1;
vector<y>v[M];
vector<pair<y,y>>r;

void d(y a,y p){
    t[a]=c;
    l[a]=c++;
    for(y n:v[a]){
        if(n==p){p=0;continue;}
        if(!t[n]){
            d(n,a);r.g({a,n});
            l[a]=min(l[a],l[n]);
        }
        else if(t[n]<t[a]){
            r.g({a,n});
            l[a]=min(l[a],t[n]);
        }
    }
}
y main(){
    y n,m,a,b,i;cin>>n>>m;
    for(i=1;i<=m;i++){
        cin>>a>>b;
        v[a].g(b);v[b].g(a);
    }
    d(1,0);
    for(i=2;i<=n;i++)
        if(l[i]==t[i]||!t[i]){
            cout << "IMPOSSIBLE";
            return 0;
        }
    for(auto[a,b]:r)cout<<a<<" "<<b<<'\n';
}
