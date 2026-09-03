#include <bits/stdc++.h>
using namespace std;
#include "../sections/geometry/integer_geometry.cpp"
#include "../sections/geometry/minkowski_sum.cpp"

bool lessIP(IP a,IP b){return tie(a.x,a.y)<tie(b.x,b.y);}
vector<IP> hull(vector<IP> p){
    sort(p.begin(),p.end(),lessIP);p.erase(unique(p.begin(),p.end(),[](IP a,IP b){return a.x==b.x&&a.y==b.y;}),p.end());
    if(p.size()<2) return p;
    vector<IP>h;
    for(IP q:p){while(h.size()>1&&cross_i(h[h.size()-2],h.back(),q)<=0)h.pop_back();h.push_back(q);}
    int low=h.size();for(int i=(int)p.size()-2;i>=0;--i){IP q=p[i];while((int)h.size()>low&&cross_i(h[h.size()-2],h.back(),q)<=0)h.pop_back();h.push_back(q);}h.pop_back();return h;
}
void sortPoints(vector<IP>&p){sort(p.begin(),p.end(),lessIP);}
int main(){
    vector<IP>a={{0,0},{2,0},{2,2},{0,2}},b={{0,0},{1,0},{1,1},{0,1}};
    auto got=minkowskiSum(a,b);vector<IP>want={{0,0},{3,0},{3,3},{0,3}};sortPoints(got);sortPoints(want);assert(got.size()==4&&equal(got.begin(),got.end(),want.begin(),[](IP x,IP y){return x.x==y.x&&x.y==y.y;}));
    mt19937 rng(17);
    for(int it=0;it<500;++it){
        vector<IP>x(8),y(8);for(auto&p:x)p={(int)(rng()%11)-5,(int)(rng()%11)-5};for(auto&p:y)p={(int)(rng()%11)-5,(int)(rng()%11)-5};
        x=hull(x);y=hull(y);if(x.size()<3||y.size()<3)continue;
        vector<IP>sums;for(IP p:x)for(IP q:y)sums.push_back(mpAdd(p,q));
        auto expected=hull(sums),actual=minkowskiSum(x,y);sortPoints(expected);sortPoints(actual);
        assert(actual.size()==expected.size());
        for(int i=0;i<(int)actual.size();++i)assert(actual[i].x==expected[i].x&&actual[i].y==expected[i].y);
    }
}
