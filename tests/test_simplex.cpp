#include <bits/stdc++.h>
using namespace std;
#include "../sections/math/simplex.cpp"

bool close(long double a,long double b){return fabsl(a-b)<1e-7L;}
int main(){using T=long double;{
    vector<vector<T>>A={{1,1},{1,0},{0,1}};vector<T>b={4,2,3},c={1,1};auto r=Simplex(A,b,c).solve();assert(r.status==0&&close(r.value,4));}
    {vector<vector<T>>A={{1}};vector<T>b={-1},c={1};assert(Simplex(A,b,c).solve().status==-1);}
    {vector<vector<T>>A={{-1}};vector<T>b={0},c={1};assert(Simplex(A,b,c).solve().status==1);}
    {vector<vector<T>>A;vector<T>b,c={1};assert(Simplex(A,b,c).solve().status==1);}
    {vector<vector<T>>A={{}};vector<T>b={-1},c;assert(Simplex(A,b,c).solve().status==-1);}
    mt19937 rng(46);auto rnd=[&]()->T{return (int)(rng()%11)-5;};for(int it=0;it<1000;++it){int m=2+rng()%5;vector<vector<T>>A={{1,0},{0,1}};vector<T>b={10,10},c={rnd(),rnd()};for(int i=0;i<m;++i){A.push_back({rnd(),rnd()});b.push_back(rng()%31);}vector<array<T,3>>line={{1,0,0},{0,1,0}};for(int i=0;i<(int)A.size();++i)line.push_back({A[i][0],A[i][1],b[i]});long double want=-1e100;for(int i=0;i<(int)line.size();++i)for(int j=i+1;j<(int)line.size();++j){T det=line[i][0]*line[j][1]-line[i][1]*line[j][0];if(fabsl(det)<1e-12)continue;T x=(line[i][2]*line[j][1]-line[i][1]*line[j][2])/det,y=(line[i][0]*line[j][2]-line[i][2]*line[j][0])/det;if(x<-1e-9||y<-1e-9)continue;bool ok=true;for(int z=0;z<(int)A.size();++z)ok&=A[z][0]*x+A[z][1]*y<=b[z]+1e-8;if(ok)want=max(want,c[0]*x+c[1]*y);}auto r=Simplex(A,b,c).solve();assert(r.status==0&&close(r.value,want));assert(r.x[0]>=-1e-8&&r.x[1]>=-1e-8);}
}
