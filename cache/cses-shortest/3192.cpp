#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k, f = 0, b, i, a, j;
    cin >> n >> k;
    vector<int> x(n);
    for (int &e : x) {
        cin >> e;
    }
    for (b = 30; b >= 0; --b) {
        for (i = f; i < n && !(x[i] & (1 << b)); ++i);
        if (i == n) continue;
        swap(x[i], x[f]);
        for (i = 0; i < n; ++i) {
            if (i != f && (x[i] & (1 << b))) {
                x[i] ^= x[f];
            }
        }
        ++f;
    }
    for (i = 0; i < k; ++i) {
        a = 0;
        for (j = i; j; j -= j&-j) {
            a ^= x[n - 1 - __builtin_ctz(j)];
        }
        cout << a << ' ';
    }
    return 0;
}
