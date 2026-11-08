#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, x, m = 250000, d=1e9+7;
    cin >> n >> a;
    vector<int> p(2*m+1),c = p;
    c[m] = 1;
    for (int i = 1; i <= n; i++){
        p = c;
        cin >> x; x -= a;
        for (int j = x; min(j, j - x) <= 2 * m; j++) c[j - x] = (c[j-x] + p[j]) % d;
    }
    cout << (c[m]+d-1)%d;
}