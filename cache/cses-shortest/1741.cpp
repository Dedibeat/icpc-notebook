#include <bits/stdc++.h>
using namespace std;

const int MX = 1000000;

int seg[10*MX],lazy[10*MX];

void upd(int v,int ul,int ur,int l,int r,int val){
  if(r < ul or l > ur or l > r) return ;
  if(ul <= l and ur >= r){
    lazy[v] += val;
  }else{
    upd(v*2,ul,ur,l,(l+r)/2,val);
    upd(v*2+1,ul,ur,(l+r)/2+1,r,val);
  }
  seg[v] = lazy[v]?r-l+1:seg[v*2]+seg[v*2+1];
}

int main() {
  int n;
  cin >> n;
  set<array<int,5>> s;
  for(int i = 0;i < n;i++){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    s.insert({b,i,a+1,c,1});
    s.insert({d,i,a+1,c,-1});
  }
  long long last = (*(s.begin()))[0];
  long long ans = 0;
  for(auto [a,b,c,d,e] : s){
    ans += seg[1]*(a-last);
    upd(1,c+MX,d+MX,0,2*MX+1,e);
    last = a;
  }
  cout << ans;
}