#include <iostream>

main() {
    int n, M = 1e9 + 7;
    std::cin >> n;
    int64_t a[n + 1] = {1, 1};
    for (int i = 4; i <= n; ++i)
        a[i] = ((a[i - 1] * (i + 1) - a[i - 2] * (i - 2) - a[i - 3] * (i - 5) + a[i - 4] * (i - 3)) % M + M) % M;
    std::cout << a[n];
}
