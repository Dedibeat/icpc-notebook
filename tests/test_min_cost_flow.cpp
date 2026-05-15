#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/min_cost_flow.cpp"

int main() {
    {
        MCMF mf(4);
        mf.addEdge(0, 1, 2, 1);
        mf.addEdge(0, 2, 1, 5);
        mf.addEdge(1, 2, 1, 1);
        mf.addEdge(1, 3, 1, 3);
        mf.addEdge(2, 3, 2, 1);
        auto [f, c] = mf.minCost(0, 3, 3);
        assert(f == 3);
        assert(c == 13);
    }
    {
        MCMF mf(3);
        mf.addEdge(0, 1, 1, -5);
        mf.addEdge(1, 2, 1, 2);
        mf.addEdge(0, 2, 1, 10);
        auto [f, c] = mf.minCost(0, 2, 2);
        assert(f == 2);
        assert(c == 7);
    }
    {
        MCMF mf(3);
        mf.addEdge(0, 1, 1, 4);
        auto [f, c] = mf.minCost(0, 2, 5);
        assert(f == 0);
        assert(c == 0);
    }
    {
        MCMF mf(2);
        mf.addEdge(0, 1, 3, 4);
        mf.addEdge(0, 1, 2, 1);
        auto [f, c] = mf.minCost(0, 1, 4);
        assert(f == 4);
        assert(c == 10);
    }
}
