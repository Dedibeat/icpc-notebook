#include <bits/stdc++.h>
using namespace std;
#include "../sections/math/sprague_grundy.cpp"

int main() {
    vector<vector<int>> g(11);
    for (int x = 1; x <= 10; ++x) for (int d : {1,2,3}) if (x >= d) g[x].push_back(x-d);
    auto sg = grundy_dag(g);
    for (int x = 0; x <= 10; ++x) assert(sg[x] == x % 4);
    assert(grundy_dag(vector<vector<int>>{{1},{0}}).empty());
    assert(grundy_dag({}).empty());
}
