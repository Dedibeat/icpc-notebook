#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/persistent_segment_tree.cpp"

void free_versions(vector<Node*> pending) {
    unordered_set<Node*> nodes;
    while (!pending.empty()) {
        Node *v = pending.back();
        pending.pop_back();
        if (!v || !nodes.insert(v).second) continue;
        pending.push_back(v->lc);
        pending.push_back(v->rc);
    }
    for (Node *v : nodes) delete v;
}

int main() {
    Node empty;
    const long long big = 1LL << 40;
    Node *a = empty.update(0, 0, 0, big);
    Node *b = a->update(0, 0, 0, -big);
    assert(empty.query(0, 0, 0, 0) == 0);
    assert(a->query(0, 0, 0, 0) == big);
    assert(b->query(0, 0, 0, 0) == 0);
    assert(a->query(0, 0, 1, 1) == 0);
    free_versions({a, b});

    Node *left = empty.update(0, INT_MAX, 0, big);
    Node *both = left->update(0, INT_MAX, INT_MAX, big);
    assert(both->query(0, INT_MAX, 0, INT_MAX) == 2 * big);
    assert(both->query(0, INT_MAX, 1, INT_MAX - 1) == 0);
    assert(both->query(0, INT_MAX, INT_MAX, INT_MAX) == big);
    assert(left->query(0, INT_MAX, INT_MAX, INT_MAX) == 0);
    free_versions({left, both});

    mt19937 rng(555);
    for (int n = 1; n <= 50; ++n) {
        vector<Node*> roots{new Node};
        vector<vector<long long>> brute(1, vector<long long>(n));
        for (int it = 0; it < 200; ++it) {
            int parent = rng() % roots.size(), p = rng() % n;
            long long delta = static_cast<long long>(rng() % 201) - 100;
            roots.push_back(roots[parent]->update(0, n - 1, p, delta));
            auto next = brute[parent];
            next[p] += delta;
            brute.push_back(next);
            assert(roots.back()->query(0, n - 1, p, p) == next[p]);
            assert(roots[parent]->query(0, n - 1, p, p) == brute[parent][p]);

            int version = rng() % roots.size();
            int l = rng() % n, r = l + rng() % (n - l);
            const auto& values = brute[version];
            long long want = accumulate(values.begin() + l, values.begin() + r + 1, 0LL);
            assert(roots[version]->query(0, n - 1, l, r) == want);
        }
        free_versions(roots);
    }
}
