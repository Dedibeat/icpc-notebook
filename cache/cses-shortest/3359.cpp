#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<string> v(n);
    for (auto &&i : v) cin >> i;
    char o, m = v[0][0];
    for (int i = 1; i < 2*n-1; i++)
    {
        cout << m;
        o = m;
        m = 0x7F;
        for (int j = min(i,n-1), k = max(0,i-n+1); j >= 0 && k < n ; j--,k++)
        {
            if((j&&v[k][j-1] == o) || (k&&v[k-1][j] == o)) m = min(m,v[k][j]);
            else v[k][j] = 0;
        }
    }
    cout << m;
}