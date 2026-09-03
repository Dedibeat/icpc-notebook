#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/topological_sort.cpp"

int main() {
    vector<vector<int>> g = {{1, 2}, {3}, {3}, {}};
    auto p = topological_sort(g);
    vector<int> at(4);
    for (int i = 0; i < 4; ++i) at[p[i]] = i;
    for (int v = 0; v < 4; ++v) for (int to : g[v]) assert(at[v] < at[to]);
    assert(topological_sort(vector<vector<int>>{{1}, {0}}).empty());
    assert(topological_sort({}).empty());
    vector<vector<int>> parallel = {{1, 1}, {}};
    assert(topological_sort(parallel).size() == 2);
}
