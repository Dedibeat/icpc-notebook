#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/euler_walk.cpp"

int main() {
    // directed cycle 0->1->2->0
    {
        vector<vector<pair<int, int>>> g(3);
        g[0].push_back({1, 0});
        g[1].push_back({2, 1});
        g[2].push_back({0, 2});
        auto w = eulerWalk(g, 3, 0);
        assert((int)w.size() == 4 && w.front() == 0 && w.back() == 0);
    }
    // directed path 0->1->2 (must start at 0)
    {
        vector<vector<pair<int, int>>> g(3);
        g[0].push_back({1, 0});
        g[1].push_back({2, 1});
        auto w = eulerWalk(g, 2, 0);
        assert((w == vector<int>{0, 1, 2}));
        assert(eulerWalk(g, 2, 1).empty()); // wrong start
    }
    // undirected: triangle + pendant edge => path between odd vertices
    {
        vector<vector<pair<int, int>>> g(4);
        auto add = [&](int u, int v, int id) {
            g[u].push_back({v, id});
            g[v].push_back({u, id});
        };
        add(0, 1, 0);
        add(1, 2, 1);
        add(2, 0, 2);
        add(0, 3, 3); // odd degrees: 0 and 3
        auto w = eulerWalk(g, 4, 3);
        assert((int)w.size() == 5 && w.front() == 3 && w.back() == 0);
        // each edge used exactly once: verify consecutive pairs are edges
        multiset<pair<int, int>> need = {{0, 1}, {1, 2}, {0, 2}, {0, 3}};
        for (int i = 0; i + 1 < (int)w.size(); i++) {
            pair<int, int> e = {min(w[i], w[i + 1]), max(w[i], w[i + 1])};
            auto it = need.find(e);
            assert(it != need.end());
            need.erase(it);
        }
        assert(need.empty());
        assert(eulerWalk(g, 4, 1).empty()); // start at even vertex fails
    }
    // no walk: two disconnected edges
    {
        vector<vector<pair<int, int>>> g(4);
        g[0].push_back({1, 0});
        g[2].push_back({3, 1});
        assert(eulerWalk(g, 2, 0).empty());
    }
    return 0;
}
