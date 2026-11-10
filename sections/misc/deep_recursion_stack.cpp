// Raise the stack limit for deep recursion (Linux). Call FIRST in main.
// O(1). Returns false on failure. Stack use counts toward memory limits.
// The default request is 256 MiB. Check depth and stack size for your DFS.
#include <sys/resource.h> // put ABOVE #define int long long
bool raise_stack(rlim_t bytes = 256 << 20) {
    rlimit rl;
    if (getrlimit(RLIMIT_STACK, &rl) != 0) return false;
    if (rl.rlim_cur == RLIM_INFINITY || rl.rlim_cur >= bytes) return true;
    if (rl.rlim_max != RLIM_INFINITY && rl.rlim_max < bytes) return false;
    rl.rlim_cur = bytes;
    return setrlimit(RLIMIT_STACK, &rl) == 0;
}
