#include "iostream"
using namespace std;
int n, l, t = 1;
int main() {
    cin >> n;
    int p[n-2], c[n+1]{};
    for (auto& x : p) cin >> x, c[x]++;
    c[p[n-3]]++;
    while (t < n && c[t]) ++t;
    l = t;
    for (auto v : p) {
        cout << v << ' ' << l << '\n';
        if (!--c[v] && v < t) l = v;
        else {
            while (++t <= n && c[t]);
            l = t;
        }
    }
    cout << p[n-3] << ' ' << l << '\n';
}

