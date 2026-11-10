#include <bits/stdc++.h>
using namespace std;
#include "../sections/geometry/geometry_base.cpp"
#include "../sections/geometry/half_plane_intersection.cpp"

bool close(T a,T b){return fabsl(a-b)<1e-9;}
T polygonArea2(const vector<P>& p){T a=0;for(int i=0;i<(int)p.size();++i)a+=cross(p[i],p[(i+1)%p.size()]);return a;}
int main(){
    vector<HalfPlane> square={{{0,0},{1,0}},{{2,0},{0,1}},{{2,2},{-1,0}},{{0,2},{0,-1}}};
    auto p=halfPlaneIntersection(square);
    assert(p.size()==4 && close(fabsl(polygonArea2(p)),8));
    square.push_back({{0,-1},{1,0}}); // redundant y >= -1
    p=halfPlaneIntersection(square);
    assert(p.size()==4 && close(fabsl(polygonArea2(p)),8));
    square.push_back({{0,3},{1,0}}); // incompatible y >= 3
    assert(halfPlaneIntersection(square).empty());
    assert(halfPlaneIntersection({{{0,0},{1,0}}}).empty()); // unbounded
    assert(halfPlaneIntersection({{{0,0},{1,0}},{{0,0},{1,1}},{{1,0},{0,1}}}).empty());
    assert(halfPlaneIntersection({{{0,0},{1,0}},{{0,1},{-1,0}}}).empty());

    // Compare against clipping a small square one constraint at a time.
    mt19937 rng(106);
    for (int it=0; it<2000; ++it) {
        vector<HalfPlane> lines(square.begin(),square.begin()+4);
        vector<P> expected = {{0,0},{2,0},{2,2},{0,2}};
        for (int j=0; j<10; ++j) {
            P v{T(rng()%7)-3,T(rng()%7)-3};
            if (v.x == 0 && v.y == 0) continue;
            HalfPlane h{{T(rng()%7)-2,T(rng()%7)-2},v};
            lines.push_back(h);
            vector<P> next;
            for (int i=0; i<(int)expected.size(); ++i) {
                P a=expected[i], b=expected[(i+1)%expected.size()];
                T da=cross(v,a-h.p), db=cross(v,b-h.p);
                if (da>=-EPS) next.push_back(a);
                if ((da<-EPS)!=(db<-EPS)) next.push_back(a+(b-a)*(da/(da-db)));
            }
            expected.swap(next);
        }
        auto got = halfPlaneIntersection(lines);
        assert(close(polygonArea2(got),polygonArea2(expected)));
        for (P x : got) for (auto h : lines) assert(!h.outside(x));
    }
}
