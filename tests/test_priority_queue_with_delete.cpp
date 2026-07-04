#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/priority_queue_with_delete.cpp"

int main() {
    Heap h;
    h.push(5);
    h.push(3);
    h.push(5);
    assert(h.size() == 3);
    assert(h.top() == 5);

    h.erase(5);
    assert(h.top() == 5);
    h.erase(5);
    assert(h.top() == 3);
    assert(h.size() == 1);

    h.push(4);
    h.erase(4);
    assert(h.top() == 3);

    h.pop();
    assert(h.size() == 0);

    // compare against multiset on random ops
    mt19937 rng(7);
    Heap rh;
    multiset<int> ms;
    for (int it = 0; it < 5000; it++) {
        int op = rng() % 3;
        if (op == 0 || ms.empty()) {
            int v = rng() % 100;
            rh.push(v);
            ms.insert(v);
        } else if (op == 1) {
            int v = *ms.begin();
            rh.erase(v);
            ms.erase(ms.find(v));
        } else {
            assert(rh.top() == *ms.rbegin());
        }
        assert(rh.size() == (int)ms.size());
    }
    return 0;
}
