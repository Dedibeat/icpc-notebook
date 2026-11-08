#include <bits/stdc++.h>

using namespace std;

main() {
    long long t, n, m, k, a, b;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k; --n; --m;
        a = k / n;
        b = k / m;
        cout << (a % 2 ? n - k % n : k % n)  + 1 << ' ' << (b % 2 ? m - k % m : k % m) + 1 << ' ' << a + b - k / lcm(n, m) << '\n';
    }
}
