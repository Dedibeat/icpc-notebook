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

    Dinic disconnected(3);
    disconnected.addEdge(0, 1, 7);
    assert(disconnected.calc(0, 2) == 0);

    Dinic zero(2);
    zero.addEdge(0, 1, 0);
    assert(zero.calc(0, 1) == 0);
}
