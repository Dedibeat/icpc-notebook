#include <bits/stdc++.h>
using namespace std;
#define I int
#define R return
 
I n, i, N;

I p(I a) {
    for (i=2; i*i<=a; i++) if (a%i==0) R 0;
    R 1;
}

I main() {
    cin >> n;
    vector<I> a(n), b(n);
    while (n) {
        N = n+1;
        while (!p(N)) N++;
        for (i=n; i>=N-n; i--) {
            a[i-1] = i;
            b[i-1] = N-i;
        }
        n = N-n-1;
    }
    for (I A:a) cout << A << ' ';
    for (I B:b) cout << B << ' ';
    R 0;
}