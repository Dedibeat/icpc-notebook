#include <iostream>
#include <cstring>

using namespace std;

int M = 1000000007;

int inv(long x) {
    int a = 1;

    for (int i = 0; i < 30; i++) {
        if ((M - 2) & (1 << i))
            a = a * x % M;

        x = x * x % M;
    }

    return a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    int a[500][501], d[500], x[500] = {};
    memset(d, -1, 2000);

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++)
            cin >> a[i][j];

    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            if (d[i] < 0 && a[i][j]) {
                d[i] = j;
                long b = inv(a[i][j]);

                for (int l = j; l <= m; l++)
                    a[i][l] = a[i][l] * b % M;

                for (int k = 0; k < n; k++)
                    if (k != i) {
                        b = M - a[k][j];

                        for (int l = j; l <= m; l++)
                            a[k][l] = (a[k][l] + b * a[i][l]) % M;
                    }

                break;
            }

    for (int i = 0; i < n; i++) {
        if (d[i] < 0 && a[i][m]) {
            cout << -1;
            return 0;
        }

        if (d[i] >= 0)
            x[d[i]] = a[i][m];
    }

    for (int j = 0; j < m; j++)
        cout << x[j] << " ";
}
