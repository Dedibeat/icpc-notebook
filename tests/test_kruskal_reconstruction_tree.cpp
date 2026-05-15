#include <bits/stdc++.h>
using namespace std;

#include "../sections/graph/kruskal_reconstruction_tree.cpp"

int main() {
    edges = {{10, 0, 3}, {1, 0, 1}, {3, 2, 3}, {2, 1, 2}};
    int root = build_kruskal_tree(4);
    assert(total_nodes == 7);
    assert(root == 6);
    assert(node_weight[root] == 3);
    assert(ktree[root].size() == 2);
    assert(node_weight[4] == 1);
    assert(node_weight[5] == 2);
}
