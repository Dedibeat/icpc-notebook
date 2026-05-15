#include <bits/stdc++.h>
using namespace std;

#include "../sections/data_structures/priority_queue_with_delete.cpp"

int main() {
    Heap h;
    h.ins(5, 1);
    h.ins(3, 1);
    h.ins(5, 1);
    assert(h.top() == 5);

    h.ins(5, -1);
    assert(h.top() == 5);
    h.ins(5, -1);
    assert(h.top() == 3);

    h.ins(4, 1);
    h.ins(4, -1);
    assert(h.top() == 3);
}
