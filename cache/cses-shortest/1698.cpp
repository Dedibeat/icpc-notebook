#include <bits/stdc++.h>
using namespace std;
#define F(i, b) for(int i = 1; i < (b); ++i)

int main() {
  int N;
  cin >> N;
  ++N;
  vector<int> v(N), p(N), c(N);
  F(i,N) cin>>p[i];
  vector<pair<int,int>> s, t;
  F(i,N) if(!v[i]) {
    int x = i, n = 0;
    while(!v[x]) {
      v[x] = 1;
      c[n++] = x;
      x = p[x];
    }
    if(n == 1) continue;
    if(n == 2) {
      s.emplace_back(c[0], c[1]);
      continue;
    }
    F(i,n-i) s.emplace_back(c[i], c[n-i]);
    F(i,n-i+1) t.emplace_back(c[i], c[(n-i+1)%n]);
  }
  cout << (size(s)>0) + (size(t)>0) << endl;
  for(auto r:{s,t}) {
    if(size(r)) cout << size(r) << endl;
    for(auto [i,j] : r) cout << i << " " << j << "\n";
  }
}
