#include <iostream>
using namespace std;

const int M = 1e9 + 7;
long t, n, a, b, f[5010], c[5010][5010], d[5010][5010];

int main() {
    f[0] = 1;
    for (n = 1; n < 5010; ++n)
        f[n] = n * f[n - 1] % M;
    for (n = 0; n < 5010; ++n) {
        c[n][0] = 1;
        for (a = 1; a <= n; ++a)
            c[n][a] = (c[n - 1][a - 1] + c[n - 1][a]) % M;
    }
    d[0][0] = 1;
    for (a = 0; a < 5009; ++a) {
        for (b = 0; b < 5009; ++b) {
            d[a][b + 1] = (d[a][b + 1] + a * d[a][b]) % M;
            d[a + 1][b] = (d[a + 1][b] + b * d[a][b]) % M;
            d[a + 1][b + 1] = (d[a + 1][b + 1] + (a + b + 1) * d[a][b]) % M;
        }
    }
    for (cin >> t; t--;) {
        cin >> n >> a >> b;
        cout << (a + b > n ? 0 : c[n][n - a - b] * d[a][b] % M * f[n] % M) << endl;
    }
}
