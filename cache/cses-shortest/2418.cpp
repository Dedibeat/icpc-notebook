#include <bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
pair<int,int>d[4]={{1,0},{-1,0},{0,1},{0,-1}};
mt19937_64 R((ull)new char);
void S(){
  int n,m,a,b,c,e;cin>>n>>m>>a>>b>>c>>e;
  for(int t=0;t<150;t++){
    int x=a,y=b,X=c,Y=e;if(t&1)swap(x,X),swap(y,Y);
    bool u[51][51];memset(u,0,sizeof u);
    auto g=[&](int i,int j){u[i][j]=1;return make_pair(i,j);};
    auto h=[&](int i,int j){return i>=1&&i<=n&&j>=1&&j<=m&&!u[i][j];};
    vector<pair<int,int>>p;p.reserve(n*m);p.push_back(g(x,y));
    for(;;){
      vector<pair<pair<int,int>,pair<int,int>>>v;v.reserve(4);
      for(auto [dx,dy]:d){
        int i=p.back().first+dx,j=p.back().second+dy;
        if(!h(i,j))continue;
        int s=0;for(auto [qx,qy]:d)s+=h(i+qx,j+qy);
        if(s<=1&&(i!=X||j!=Y)){v.assign(1,{{1,1},{i,j}});break;}
        v.push_back({{abs(i-X)+abs(j-Y),max(abs(i-X),abs(j-Y))},{i,j}});
      }
      if(v.empty())break;
      sort(v.begin(),v.end());
      int k=(int)v.size()-1;
      while(k&&!(R()%(p.size()+5)))--k;
      p.push_back(g(v[k].second.first,v[k].second.second));
    }
    if(p.size()==(size_t)n*m&&p.back()==make_pair(X,Y)){
      cout<<"YES\n";
      if(t&1)reverse(p.begin(),p.end());
      for(size_t i=0;i+1<p.size();i++){
        auto [x1,y1]=p[i];auto [x2,y2]=p[i+1];
        cout<<(x1==x2?(y1<y2?'R':'L'):(x1<x2?'D':'U'));
      }
      cout<<"\n";return;
    }
  }
  cout<<"NO\n";
}
int main(){
  ios::sync_with_stdio(false);cin.tie(nullptr);
  int t;cin>>t;while(t--)S();
}