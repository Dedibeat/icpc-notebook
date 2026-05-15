#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F first 
#define S second 
#define all(x) (x).begin(), (x).end()
#define log(x) cout << #x << " = " << x << " "
#define logl(x) cout << #x << " = " << x << endl
#define print(a) cout << #a << " = "; \
for(auto x: a) cout << x << " "; cout << endl;
template<typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p)
{
    return os << "(" << p.F << "," << p.S << ")";
}
const int N = 5e3 + 5;
int a[N], pref[N];
int dp[N][N], opt[N][N];
int C(int l, int r)
{
    return pref[r] - pref[l - 1];
}
int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(NULL); 
    int n; cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    for(int i = 1; i <= n; i++)
        opt[i][i] = i;
 
    for(int len = 2; len <= n; len++)
    {
        for(int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            int lo = opt[i][j - 1];
            int hi = opt[i + 1][j];
            pair<int, int> best = {1e18, -1};
            for(int k = max(i, lo); k <= min(hi, j - 1); k++)
            {
                best = min(best, make_pair(dp[i][k] + dp[k + 1][j], k));
            }
            dp[i][j] = best.first + C(i, j);
            opt[i][j] = best.second;
            assert(opt[i][j] != -1);
        }
    }
    cout << dp[1][n] << "\n";
