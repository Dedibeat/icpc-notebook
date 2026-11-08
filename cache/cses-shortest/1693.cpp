#import <bits/stdc++.h>
using namespace std;

int n, m, u, i, v, d['   '];
vector<int> S['   '], A;

void E(int u) {
    while (S[u].size())
        v = S[u].back(), S[u].pop_back(), E(v);
    A.push_back(u);
}

main() {
    for(cin >> n >> m; i++ < m; --d[v])
        cin >> u >> v, S[v].push_back(u), ++d[u];

    E(n);
    if (d[1]-1 | d[n]+1 | A.size()-m-1 | A[0]-1)
        cout << "IMPOSSIBLE";
    else for(int v : A)
        cout << v << ' ';

}