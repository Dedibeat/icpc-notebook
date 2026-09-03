#include <bits/stdc++.h>
using namespace std;
#include "../sections/dp/slope_trick.cpp"

int main(){mt19937 rng(41);const int M=500,INF=1e9;for(int it=0;it<300;++it){SlopeTrick f;vector<long long>d(2*M+1);for(int op=0;op<80;++op){int type=rng()%5,a=(int)(rng()%41)-20;if(type==0){f.addAMinusX(a);for(int x=-M;x<=M;++x)d[x+M]+=max(0,a-x);}if(type==1){f.addXMinusA(a);for(int x=-M;x<=M;++x)d[x+M]+=max(0,x-a);}if(type==2){f.addAbs(a);for(int x=-M;x<=M;++x)d[x+M]+=abs(x-a);}if(type==3){int c=(int)(rng()%11)-5;f.addConstant(c);for(auto&x:d)x+=c;}if(type==4){int l=(int)(rng()%5)-2,r=l+(int)(rng()%5);f.shift(l,r);vector<long long>nd(2*M+1,INF);for(int x=-M;x<=M;++x)for(int y=max(-M,x-r);y<=min(M,x-l);++y)nd[x+M]=min(nd[x+M],d[y+M]);d.swap(nd);}for(int x=-100;x<=100;x+=5)assert(f.value(x)==d[x+M]);assert(f.minimum()==*min_element(d.begin(),d.end()));}}}
