#import <bits/stdc++.h>
using namespace std;

int v['   '], i, j, n;
string s;

main () {
    cin >> s;
    n = s.size();

    for (*v = --j; i < n; v[++i] = ++j)
        for (; j + 1 && s[i] ^ s[j];) j = v[j];

    for (; i = v[i], 1+i;) 
        cout << n - i << " ";
}
