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
}
