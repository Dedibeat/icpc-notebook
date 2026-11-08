#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int n, m, nxt[105];
long long dp[1005][105];
string s;

int main() {
    cin >> n >> s;
    m = (int)s.size();
    int i, j;
    for(i = 0, j = nxt[0] = -1;  i < m;)
        if(j == -1 || s[i] == s[j])
            nxt[++ i] = ++ j;
        else
            j = nxt[j];
    dp[0][0] = 1;
    for(int i = 1; i <= n; i += 1) {
        (dp[i][m] += 26ll * dp[i - 1][m]) %= mod;
        for(int j = 0; j < m; j += 1) {
            for(char c = 'A'; c <= 'Z'; c += 1) {
                int go = -1;
                for(int t = j; ~t; t = nxt[t])
                    if(s[t] == c) {
                        go = t;
                        break;
                    }
                (dp[i][go + 1] += dp[i - 1][j]) %= mod;
            }
        }
    }
    cout << dp[n][m] << endl;
}
