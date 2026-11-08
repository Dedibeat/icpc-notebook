#include <bits/stdc++.h>

using namespace std;
const int c=502;
int ert[c][c], n, m, db;
bool v[c];
bool dfs(int a) {
    if (a==n) {
        return true;
    }
    v[a]=true;
    for (int i=1; i<=n; i++) {
        if (!v[i] && ert[a][i]) {
            if (dfs(i)) {
                ert[a][i]--, ert[i][a]++;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i=1; i<=m; i++) {
        int a, b; cin >> a >> b;
        ert[a][b]=ert[b][a]=1;
    }
    while (dfs(1)) {
        db++;
        for (int i=1; i<=n; i++) {
            v[i]=0;
        }
    }
    cout << db << "\n";
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            if (!v[i] && v[j] && ert[i][j]==2) {
                cout << i << " " << j << "\n";
            }
        }
    }
    return 0;
}
