#include <bits/stdc++.h>
#define U << " " << 1+
using namespace std;

int n, x, i, j, k, v['  '];
map<int, int> m;

int main () {
    for (cin >> n >> x; cin >> v[j++];);

    for (; i < n; i++) {
        for (j = i+1; j < n; j++)
            if (m.count(k = x - v[i] - v[j]))
                return cout << i+1 U j U m[k] / '  ' U m[k] % '  ', 0;

        for (j = 0; j < i; j++)
            m[v[i] + v[j]] = i*'  ' + j;
    }
    cout << "IMPOSSIBLE";
}
