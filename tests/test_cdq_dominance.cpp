#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/cdq_dominance.cpp"

int main() {
    mt19937 rng(13);
    assert(dominance_count({}).empty());
    for (int n=1;n<=60;++n) for (int it=0;it<40;++it) {
        vector<Point3> p(n);
        for(auto& q:p) q={(int)(rng()%9)-4,(int)(rng()%9)-4,(int)(rng()%9)-4};
        auto got=dominance_count(p);
        for(int i=0;i<n;++i) {
            long long want=0;
            for(int j=0;j<n;++j) if(i!=j && p[j].x<=p[i].x && p[j].y<=p[i].y && p[j].z<=p[i].z) ++want;
            assert(got[i]==want);
        }
    }
}
