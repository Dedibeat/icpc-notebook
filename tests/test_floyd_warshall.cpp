#include <bits/stdc++.h>
using namespace std;
#include "../sections/graph/floyd_warshall.cpp"

int main() {
    const long long INF = 1LL << 60;
    vector<vector<long long>> d(4, vector<long long>(4, INF));
    for (int i = 0; i < 4; ++i) d[i][i] = 0;
    d[0][1] = 5; d[1][2] = -2; d[0][2] = 10;
    floyd_warshall(d, INF);
    assert(d[0][2] == 3 && d[3][0] == INF);

    vector<vector<long long>> neg = {{0, 1}, {-3, 0}};
    floyd_warshall(neg, INF);
    assert(neg[0][0] < 0 && neg[1][1] < 0);
}
