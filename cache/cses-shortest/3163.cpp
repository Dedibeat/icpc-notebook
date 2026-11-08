#include<bits/stdc++.h>
#define I int
using namespace std;
const I N = 3e5;
struct s{I k, l, r, i, d;} v[N*3];
I n, q, P, b[N], a[N], i, A,B,C,D;
I operator<(s a, s b) {return a.k!=b.k ? a.k<b.k : a.d<b.d;}
I Q(I p, I r=0) {for(; p; p-=(p&-p)) r+=b[p]; return r;}
I main() {
  cin >> n >> q;
  for(;i<n;) cin >> A, v[P++] = s{A, i+2, i++, 0, -2};
  for(i=0; i<q;) {
    cin >> A >> B >> C >> D;
    v[P++] = s{C-1, A, B, i,  -1};
    v[P++] = s{D  , A, B, i++, 1};
  }
  sort(v, v+P);
  for(auto [k,l,r,i,d] : v) {
    if(d+2) a[i] += (Q(r+1)-Q(l)) * d;
    else for(; l<N; l+=(l&-l)) b[l]++;
  }
  for(i=0; i<q;) cout << a[i++] << '\n';
}