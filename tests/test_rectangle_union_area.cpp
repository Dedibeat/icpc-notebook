#include <bits/stdc++.h>
using namespace std;
#include "../sections/geometry/rectangle_union_area.cpp"

int main(){
    assert(rectangleUnionArea({})==0);
    assert(rectangleUnionArea({{0,0,2,2},{1,1,3,3}})==7);
    assert(rectangleUnionArea({{LLONG_MIN,0,LLONG_MAX,1}})==(__int128)ULLONG_MAX);
    assert(rectangleUnionArea({{0,LLONG_MIN,1,LLONG_MAX}})==(__int128)ULLONG_MAX);
    mt19937 rng(19);
    for(int it=0;it<1000;++it){
        vector<Rectangle>r(rng()%8);for(auto&z:r){z={(int)(rng()%11)-5,(int)(rng()%11)-5,(int)(rng()%11)-5,(int)(rng()%11)-5};if(z.x1>z.x2)swap(z.x1,z.x2);if(z.y1>z.y2)swap(z.y1,z.y2);}
        long long want=0;for(int x=-5;x<5;++x)for(int y=-5;y<5;++y){bool in=false;for(auto z:r)in|=z.x1<=x&&x<z.x2&&z.y1<=y&&y<z.y2;want+=in;}
        assert(rectangleUnionArea(r)==want);
    }
}
