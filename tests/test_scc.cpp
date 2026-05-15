#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/scc.cpp"

int main() {
    SCC s(6);
    s.addEdge(0, 1);
    s.addEdge(1, 2);
    s.addEdge(2, 0);
    s.addEdge(2, 3);
    s.addEdge(3, 4);
    s.addEdge(4, 3);
    int c = s.build();
    assert(c == 3);
    assert(s.comp[0] == s.comp[1] && s.comp[1] == s.comp[2]);
    assert(s.comp[3] == s.comp[4]);
    assert(s.comp[2] != s.comp[3]);
    assert(s.comp[5] != s.comp[0] && s.comp[5] != s.comp[3]);

    SCC one(1);
    assert(one.build() == 1);
    assert(one.comp[0] == 0);
}
