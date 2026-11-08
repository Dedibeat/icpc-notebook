#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int p[2][3001][26];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    ll a = 0;
    fill(**p, **p + 2 * 3001 * 26, 1);
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int x = i & 1;
        for (int j = 0; j < n; ++j) {
            int m = 0;
            for (int o = 0; o < k; ++o) {
                p[x][j+1][o] = 1;
                if (s[j] != 'A' + o)
                    p[x][j+1][o] += min({p[x][j][o], p[!x][j][o], p[!x][j+1][o]});
                m = max(m, p[x][j+1][o]);
            }
            a += min(i, j) + 2 - m;
        }
    }
    cout << a;
}
