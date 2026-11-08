#import <bits/stdc++.h>
using namespace std;

#pragma GCC target "avx"

long n, a, l, r;
bitset<3020> g['  ']; 

main() {
    for (cin >> n; cin >> g[r = ++l]; )
        for (; r--; a += n*n--)
            n = (g[l] & g[r]).count();
    cout << a/2;
}