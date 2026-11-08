#include <bits/stdc++.h>

using namespace std;

main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    if (n < 4) {
        cout << "IMPOSSIBLE";
        return 0;
    }
    if (n < 5) {
        cout << "1 1 1 2\n1 2 3 4\n2 2 4 4\n3 3 3 4";
        return 0;
    }
    for (int i = 0; i < n - 2; ++i) {
        for (int j = 0; j < n - 2; ++j) {
            cout << (i + j) % (n - 2) + 2 << ' ';
        }
        cout << "1 " << n - i - 1 << '\n';
    }
    for (int i = 0; i < n - 1; ++i) {
        cout << n - i - 1 << ' ';
    }
    cout << "1\n";
    for (int i = 0; i < n; ++i) cout << n << ' ';
}
