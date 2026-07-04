#include <bits/stdc++.h>
using namespace std;

#include "../sections/misc/deep_recursion_stack.cpp"

// each frame keeps a volatile buffer alive so ~2e6 depth needs ~100MB+ stack,
// well past the common 8MB default
long long deep(int d) {
    volatile char pad[48];
    pad[0] = (char)d;
    if (d == 0) return pad[0];
    return deep(d - 1) + (d % 2);
}

int main() {
    if (!raise_stack()) {
        // hard limit too low in this environment; nothing to verify
        printf("skipped: hard stack limit too low\n");
        return 0;
    }
    long long r = deep(2000000);
    assert(r == 1000000);
    return 0;
}
