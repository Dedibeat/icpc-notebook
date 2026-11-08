#include <bits/stdc++.h>

using namespace std;

main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k, d, i, j, c, x, y;
    cin >> n >> k;
    string G[n];
    int t = (1 << k) - 1;
    for (auto &s : G) cin >> s;
    long long a = 0;
    for (i = 0; i < n; ++i) {
        vector<int> M(n, 0);
        for (j = i; j < n; ++j) {
            stack<int> I, O;
            x = y = 0;
            for (c = 0; c < n; ++c) {
                M[c] |= (1 << (G[j][c] - 'A'));
                I.push(M[c]);
                x |= M[c];
                while ((x | y) == t) {
                    a += n - c;
                    if (O.empty()) {
                        while (!I.empty()) {
                            y |= I.top();
                            O.push(y);
                            I.pop();
                        }
                        x = 0;
                    }
                    O.pop();
                    y = O.empty() ? 0 : O.top();
                }
            }
        }
    }
    cout << a;
}
