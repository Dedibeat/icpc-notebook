#include<bits/stdc++.h>
using namespace std;
struct F{int a,b;int c()const{return(a+b-1)/b;}int d()const{return a/(b+1);}};
bool operator<(F x,F y){return x.c()<y.c();}
bool operator>(F x,F y){return x.d()<y.d();}
int main(){
    int n,m,a,l=0,r=1e9,x,y;cin>>n>>m;
    priority_queue<F>L;
    priority_queue<F,vector<F>,greater<F>>R;
    while(n--)cin>>a,l=max(l,a),r=min(r,a),L.push({a,1}),R.push({a,1});
    x=r,y=l;queue<F>Q;multiset<int>D;
    while(m--){
        auto f=R.top();R.pop();r=min(r,f.d());R.push({f.a,f.b+1});
        f=L.top();L.pop();x=min(x,f.d());L.push({f.a,f.b+1});
        y=min(y,L.top().c());Q.push({y,x});D.insert(y-x);
        while(!Q.empty()&&Q.front().b>=r){
            f=Q.front();Q.pop();l=min(l,f.a);D.erase(D.find(f.a-f.b));
        }
        cout<<(D.empty()?l-r:min(l-r,*D.begin()))<<' ';
    }
}