#include<bits/stdc++.h>
using namespace std;
long n,k,m=1e9+7,r,t,i,j,y;
#define v vector<vector<long>>
v l(v a,v b){
    v r(a.size(),vector<long>(b[0].size()));
    for(i=0;i<a.size();i++)
        for(j=0;j<b[0].size();j++)
            for(y=0;y<b.size();y++)
                r[i][j]+=a[i][y]*b[y][j],r[i][j]%=m;
    return r;
}
v p(v a,int b){
    if(b==1)return a;
    v t=p(a,b/2);
    t=l(t,t);
    if(b&1)t=l(a,t);
    return t;
}
main(){
    for(cin>>n;cin>>n>>k;cout <<r<<" "){
    vector<int> s;
    for(i=2;i*i<=1e9;i++){
        for(t=0;k%i==0;)t++,k/=i;
        if(t)s.push_back(t);
    }
    if(k!=1)s.push_back(1);
    r=1;
    for(int t:s)
        r*=l(p({{1,t},{1,0}},n),{{1},{1}})[0][0],r%=m;
    }
}