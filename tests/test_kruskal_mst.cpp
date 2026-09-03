#include <bits/stdc++.h>
using namespace std;
#include "../sections/data_structures/dsu.cpp"
#include "../sections/graph/kruskal_mst.cpp"

int main() {
    vector<MSTEdge> e = {{0,1,5},{0,1,2},{1,2,-4},{0,2,10},{3,3,-100}};
    auto [w, used] = kruskal_mst(4, e);
    assert(w == -2 && used == 2); // vertex 3 is disconnected; self-loop ignored
    tie(w, used) = kruskal_mst(1, {});
    assert(w == 0 && used == 0);
}
