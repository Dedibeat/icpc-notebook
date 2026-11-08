#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+1, INF = 4*N;

void upd(vector<int>& T, int i, int v){for(;i<N;i+=i&-i)T[i]=min(T[i],v);}
int qry(vector<int>& T,int i,int r=INF){for(;i;i-=i&-i)r=min(r,T[i]);return r;}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;cin>>n>>m;
    vector<array<int,3>> A(n+m);
    for(int i=0,x,y;i<n+m;i++)cin>>x>>y,A[i]={x,y,i};
    sort(A.begin(),A.end());
    vector<int> R(m,INF);
    for(int s:{-1,1}){
        vector<int> U(N,INF),D(N,INF);
        for(auto [x,y,i]:A)
            if(i<n)upd(U,N-y,s*x+y),upd(D,y,s*x-y);
            else R[i-n]=min({R[i-n],-s*x-y+qry(U,N-y),-s*x+y+qry(D,y)});
        reverse(A.begin(),A.end());
    }
    cout<<*max_element(R.begin(),R.end());
}
