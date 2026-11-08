#import<bits/stdc++.h>
using namespace std;
 
#define L int
 
L n, x, a[101], D[101][101][10001], X;
 
long R (L i, L j, L k) {
    L&Y=D[i][j][k];
    return !i--?!j & k <= x:~Y?Y:Y = (R(!!j*i, j - 1, k - a[i]) * j + R(i, j, k) * (j+1) + R(i, j + 1, k + a[i])) % 1000000007;
}
 
main () {
    memset(D, -1, sizeof D);
    for (cin >> n >> x ; cin >> a[X++] ; ) ;
    sort(a, a+n);
    cout << R(n,0,0);
}