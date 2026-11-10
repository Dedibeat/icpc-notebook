#include <bits/stdc++.h>
using namespace std;

#include "../sections/geometry/integer_geometry.cpp"

int main() {
    assert(ori_i({0, 0}, {1, 0}, {1, 1}) == 1);
    assert(ori_i({0, 0}, {1, 0}, {1, -1}) == -1);
    assert(ori_i({0, 0}, {1, 0}, {5, 0}) == 0);

    IP a{1000000000LL, 1000000000LL};
    IP b{-1000000000LL, 1000000000LL};
    IP c{1000000000LL, -1000000000LL};
    assert(ori_i(a, b, c) == 1);

    IP d{-1000000000LL, -1000000000LL};
    i128 area = cross_i(a, b, d);
    assert(area == (i128)4000000000000000000LL);
    assert(cross_i({LLONG_MIN,0},{LLONG_MAX,0},{0,1}) == (i128)ULLONG_MAX);

    const long long B = 1000000000000000LL;
    vector<IP> square={{-B,-B},{B,-B},{B,B},{-B,B}};
    assert(area2_i(square)==(i128)8*B*B);
    assert(inPolygon_i(square,{0,0})==1);
    assert(inPolygon_i(square,{B,0})==0);
    assert(inPolygon_i(square,{B+1,0})==-1);
    reverse(square.begin(),square.end());
    assert(area2_i(square)==-(i128)8*B*B);
    assert(inPolygon_i(square,{0,0})==1);
    assert(segInter_i({-B,-B},{B,B},{-B,B},{B,-B}));
    assert(!inTriStrict_i({0,0},{1,1},{2,2},{1,0}));
    assert(inTriStrict_i({0,0},{0,4},{4,0},{1,1}));
    assert(!inTriStrict_i({0,0},{0,4},{4,0},{2,2}));
    assert(area2_i({})==0 && inPolygon_i({}, {0,0})==-1);
    assert(inPolygon_i({{1,1}},{1,1})==0);
    assert(inPolygon_i({{1,1}},{0,0})==-1);
    assert(inPolygon_i({{0,0},{2,0}},{1,0})==0);
    assert(hull_i({}).empty());
    assert(hull_i({{1,1},{1,1}}).size()==1);
    assert((hull_i({{2,2},{0,0},{1,1}})==vector<IP>{{0,0},{2,2}}));

    // Exhaustive segment intersection vs parametric intersection oracle.
    vector<IP> pts;
    for(int x=-2;x<=2;++x) for(int y=-2;y<=2;++y) pts.push_back({x,y});
    auto det=[](long long x,long long y,long long u,long long v){return x*v-y*u;};
    auto between=[](IP a,IP b,IP q){
        return (b.x-a.x)*(q.y-a.y)==(b.y-a.y)*(q.x-a.x) &&
            min(a.x,b.x)<=q.x && q.x<=max(a.x,b.x) &&
            min(a.y,b.y)<=q.y && q.y<=max(a.y,b.y);
    };
    for(IP a:pts) for(IP b:pts) for(IP c:pts) for(IP d:pts) {
        long long den=det(b.x-a.x,b.y-a.y,d.x-c.x,d.y-c.y);
        bool want;
        if(!den) want=between(a,b,c)||between(a,b,d)||between(c,d,a)||between(c,d,b);
        else {
            long long t=det(c.x-a.x,c.y-a.y,d.x-c.x,d.y-c.y);
            long long u=det(c.x-a.x,c.y-a.y,b.x-a.x,b.y-a.y);
            if(den<0) den=-den,t=-t,u=-u;
            want=0<=t&&t<=den&&0<=u&&u<=den;
        }
        assert(segInter_i(a,b,c,d)==want);
    }
    // Concave polygon: winding-number oracle with independent small arithmetic.
    vector<IP> poly={{0,0},{6,0},{6,2},{2,2},{2,6},{0,6}};
    for(int pass=0;pass<2;++pass) {
        for(int x=-1;x<=7;++x) for(int y=-1;y<=7;++y) {
            IP q{x,y}; int winding=0; bool boundary=false;
            for(int i=0;i<(int)poly.size();++i) {
                IP a=poly[i],b=poly[(i+1)%poly.size()];
                boundary |= between(a,b,q);
                auto cr=det(b.x-a.x,b.y-a.y,q.x-a.x,q.y-a.y);
                if(a.y<=q.y && b.y>q.y && cr>0) ++winding;
                if(a.y>q.y && b.y<=q.y && cr<0) --winding;
            }
            assert(inPolygon_i(poly,q)==(boundary?0:winding?1:-1));
        }
        reverse(poly.begin(),poly.end());
    }
    poly.push_back(poly.front()); assert(inPolygon_i(poly,{1,1})==1);
    // Random hull vs brute supporting edges after removing points on segments.
    mt19937 rng(131);
    for(int it=0;it<500;++it) {
        vector<IP> p(1+rng()%10);
        for(auto& q:p) q=pts[rng()%pts.size()];
        auto h=hull_i(p);
        sort(p.begin(),p.end()); p.erase(unique(p.begin(),p.end()),p.end());
        vector<IP> want;
        for(IP a:p) {
            bool interior=false;
            for(IP b:p) for(IP c:p)
                if(!(a==b)&&!(a==c)&&!(b==c)&&between(b,c,a)) interior=true;
            bool support=p.size()==1;
            for(IP b:p) if(!(a==b)) {
                bool pos=false,neg=false;
                for(IP c:p) {
                    auto v=det(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
                    pos |= v>0; neg |= v<0;
                }
                support |= !(pos&&neg);
            }
            if(support&&!interior) want.push_back(a);
        }
        if(h.size()>=3) {
            assert(area2_i(h)>0);
            for(IP q:p) assert(inPolygon_i(h,q)>=0);
        }
        assert(h.front()==p.front());
        sort(h.begin(),h.end()); assert(h==want);
    }
}
