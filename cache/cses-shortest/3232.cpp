#include <iostream>
using namespace std;

const int L = 501, M = 1e9 + 7;
long N, n, k, s, dp[L][L], c[L][L], p2[L * L];

int main() {
    cin >> N;
    c[0][0] = 1;
    for (n = 1; n <= N; ++n) {
        c[n][0] = 1;
        for (k = 1; k <= n; ++k)
            c[n][k] = (c[n - 1][k - 1] + c[n - 1][k]) % M;
    }
    p2[0] = 1;
    for (n = 1; n < N * N; ++n)
        p2[n] = 2 * p2[n - 1] % M;
    dp[1][1] = 1;
    for (n = 2; n <= N; ++n) {
        dp[n][1] = p2[n * (n - 1) / 2];
        for (k = 2; k <= n; ++k) {
            for (s = 1; s + k - 1 <= n; ++s) {
                dp[n][k] += c[n][s] * dp[n - s][k - 1] % M * dp[s][1] % M;
                dp[n][k] %= M;
            }
            dp[n][1] = (dp[n][1] + M - dp[n][k]) % M;
        }            
    }
    for (k = 1; k <= N; ++k)
        cout << dp[N][k] << "\n";
}
