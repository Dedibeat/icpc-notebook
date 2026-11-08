#include <bits/stdc++.h>
#define H insert
#define Z int
#define Y(a,b) *E[a].lower_bound(A[b])
using namespace std;const Z N=2e5;Z n,m,q,a,b,A[N],B[N];set<Z>D[N],E[N];map<Z,Z>F[N];void t(Z u,Z p){A[u]=B[u]=++n;E[u].H(n);F[u][n]=1;for(Z v:D[u])if(v-p)if(!A[v]){t(v,u);B[u]=min(B[u],B[v]);E[u].H(n);F[u][n]=B[v]<A[u];}else B[u]=min(B[u],A[v]);E[u].H(N);F[u][N]=1;}Z main(){cin>>m>>m>>q;while(m--){cin>>a>>b;D[a].H(b);D[b].H(a);}t(1,0);while(q--){cin>>a>>b>>n;if(a-n&&b-n){Z x=Y(n,a),y=Y(n,b);if(x==y||F[n][x]&&F[n][y]){puts("YES");continue;}}puts("NO");}}