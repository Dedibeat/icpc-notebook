#import <bits/stdc++.h>
using namespace std; 
vector<long> a;
long n, s,i=1,p;
main() {
    cin >> n, a.resize(n + 2, 2e18);
    for (; i <= n; cin >> a[i++]);
    for (; a.size() > 3; ) {
        for (p = 1; a[p] > a[p + 2]; ++p);
        s += (a[p] += a[p + 1]);
        a.erase(a.begin() + p + 1);
        for (; a[p] > a[p - 1]; --p)
		swap(a[p], a[p-1]);
    }
    cout << s;
}