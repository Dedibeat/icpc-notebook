#include <iostream>
#define y(a,b)({T R{};for(L i=0;i<n;i++)for(L j=0;j<n;j++)for(L k=0;k<n;k++)(R._[i][j]+=a._[i][k]*b._[k][j]%M)%=M;R;})
#define z(b)({T r{};for(L i=0;i<n;i++)for(L j=0;j<n;j++)r._[i][j]=i==j;for(;k;b=y(b,b),k>>=1)if(k&1)r=y(r,b);r;})
using L=long;const L M=1e9+7;L n,k,a,b;struct T{L _[100][100];}Z;main(){std::cin>>n>>k>>k;while(std::cin>>a>>b)Z._[a-1][b-1]++;std::cout<<z(Z)._[0][n-1];}
