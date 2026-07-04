// Raise the stack limit for deep recursion (Linux). Call FIRST in main.
// Default stack is often 8MB: a DFS on a 1e6-vertex chain overflows it
// (each frame is ~50-200B, more with std::function). 256MB fixes all
// recursive snippets in this notebook (SCC, HLD, LCA, sack, tree DPs).
// Returns false if the hard limit forbids it (then convert to iterative).
#include <sys/resource.h>
bool raise_stack(rlim_t bytes = 256 << 20) {
    rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    if (rl.rlim_max != RLIM_INFINITY && rl.rlim_max < bytes) return false;
    rl.rlim_cur = bytes;
    return setrlimit(RLIMIT_STACK, &rl) == 0;
}
