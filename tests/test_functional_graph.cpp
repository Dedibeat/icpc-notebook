#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/functional_graph.cpp"

int brute_go(const vector<int>& nxt, int v, unsigned long long k) {
    vector<int> at, first(nxt.size(), -1);
    while (first[v] == -1) {
        first[v] = at.size();
        at.push_back(v);
        v = nxt[v];
    }
    if (k < at.size()) return at[k];
    int start = first[v], len = at.size() - start;
    return at[start + (k - start) % len];
}

int main() {
    vector<int> nxt = {1,2,0,2,3,6,5};
    FunctionalGraph f(nxt);
    for (int v = 0; v < 7; ++v) for (unsigned long long k : {0ULL,1ULL,2ULL,10ULL,1000000000000000000ULL}) {
        assert(f.go(v, k) == brute_go(nxt, v, k));
    }
    assert(f.dist[4] == 2 && f.entry[4] == 2 && f.cycle[4] == f.cycle[0]);
    assert(f.dist[5] == 0 && f.dist[6] == 0 && f.cycle[5] != f.cycle[0]);
}
