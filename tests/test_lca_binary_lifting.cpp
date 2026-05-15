#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/lca_binary_lifting.cpp"

int main() {
    LCA t(7);
    t.addEdge(0, 1);
    t.addEdge(0, 2);
    t.addEdge(1, 3);
    t.addEdge(1, 4);
    t.addEdge(2, 5);
    t.addEdge(5, 6);
    t.build(0);
    assert(t.lca(3, 4) == 1);
    assert(t.lca(3, 6) == 0);
    assert(t.lca(5, 6) == 5);
    assert(t.lca(0, 6) == 0);
    assert(t.lca(4, 4) == 4);
    assert(t.dist(3, 4) == 2);
    assert(t.dist(3, 6) == 5);
    assert(t.lift(6, 2) == 2);
}
