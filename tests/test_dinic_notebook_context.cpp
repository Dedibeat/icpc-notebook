#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/dinic_2.cpp"

int main() {
    Dinic d(4);
    d.addEdge(0, 1, 3);
    d.addEdge(0, 2, 2);
    d.addEdge(1, 2, 1);
    d.addEdge(1, 3, 2);
    d.addEdge(2, 3, 4);
    assert(d.calc(0, 3) == 5);
    assert(d.leftOfMinCut(0));
    assert(!d.leftOfMinCut(1));
    assert(!d.leftOfMinCut(2));
    assert(!d.leftOfMinCut(3));
    vector<pair<int, int>> cut = d.minCutEdges();
    sort(cut.begin(), cut.end());
    assert((cut == vector<pair<int, int>>{{0, 1}, {0, 2}}));

    Dinic disconnected(3);
    disconnected.addEdge(0, 1, 7);
    assert(disconnected.calc(0, 2) == 0);
    assert(disconnected.leftOfMinCut(0));
    assert(disconnected.leftOfMinCut(1));
    assert(!disconnected.leftOfMinCut(2));
    assert(disconnected.minCutEdges().empty());

    Dinic zero(2);
    zero.addEdge(0, 1, 0);
    assert(zero.calc(0, 1) == 0);
    assert(zero.leftOfMinCut(0));
    assert(!zero.leftOfMinCut(1));
    assert(zero.minCutEdges().empty());
}
