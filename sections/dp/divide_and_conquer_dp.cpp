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
const int N = 3e5 + 5;
int n, m;
vector<int> dp_bef, dp_cur;
int a[N], pref[N];
int cost(int l, int r)
{
    int sum = pref[r] - pref[l - 1];
    return sum * sum;
}
void comp(int l, int r, int lo, int hi)
{
    if(l > r) return;
    int mid = (l + r) / 2;
    pair<int, int> best = {(int)1e18, -1};
    for(int k = lo; k <= min(hi, mid); k++)
    {
        best = min(best, make_pair((k ? dp_bef[k - 1] : 0) + cost(k, mid), k));
    }
    //log(l); log(r); log(mid); logl(best);
    dp_cur[mid] = best.first;
    int opt = best.second;
    assert(opt != -1);
    comp(l, mid - 1, lo, opt);
    comp(mid + 1, r, opt, hi);
}
int32_t main()
{
    ios::sync_with_stdio(0); cin.tie(NULL); 
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    dp_bef.assign(n + 1, 0);
    dp_cur.assign(n + 1, 0);
    for(int j = 1; j <= n; j++) dp_cur[j] = cost(1, j);
    dp_bef = dp_cur;
    //print(dp_bef);
    for(int i = 2; i <= m; i++)
    {
        comp(1, n, 1, n);
        dp_bef = dp_cur;
        //print(dp_cur);
    }
    cout << dp_cur[n] << '\n';
}