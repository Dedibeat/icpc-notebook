#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll MX = 1ll << 40, P = 1ll << 18;
ll n, x[40], dp[2][P], ans[MX / P];
vector<ll> lst[P];

void print(ll msk) {
    cout << __builtin_popcountll(msk) << endl;
    for (int i = 0; i < n; ++i) {
        if (msk & (1ll << i))
            cout << x[i] << " ";
    }
    cout << endl;
}
void rec(ll cur, ll msk, ll sum, ll mxid) {
    if (cur == 0) {
        if (ans[sum / P]) {
            ll pmsk = ans[sum / P];
            ll co = msk & pmsk;
            print(msk ^ co);
            print(pmsk ^ co);
            exit(0);
        }
        else
            ans[sum / P] = msk;
    }
    for (ll j : lst[cur]) {
        if (j >= mxid)
            return;
        rec((cur + MX - x[j]) % P, msk | (1ll << j), sum + x[j], j);
    }
}
int main() {
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> x[i];
    
    ll s = max((1ll << n) / P, 1ll);
    dp[0][0] = dp[1][0] = 1;
    for (ll j = 0; j < n; ++j) {
        for (ll i = 0; i < P; ++i) {
            if (dp[0][i] == 0)
                continue;
            ll nxt = (i + x[j]) % P;
            dp[1][nxt] += dp[0][i];
            lst[nxt].push_back(j);
        }
        for (ll i = 0; i < P; ++i)
            dp[0][i] = dp[1][i];
    }
    for (ll i = 0; i < P; ++i)
        if (dp[0][i] > s - (i + 1 == P))
            rec(i, 0, 0, n);
}
