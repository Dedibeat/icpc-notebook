#import <iostream>
using namespace std;

#define y return

int n, k, l, r, m; 
int q(int x, char f='F') {
    if (x < 1) y 1e9;
    if (x > n) y 0;

    cout << f << " " << x << endl;
    cin >> x;
    y x;
}

main() {
    cin >> n >> k;

    for (r = k; m = (l+r)/2, l <= r; )
        q(m+1,'S')>q(k-m) ? l = m+1 : r = m-1;

    l = min(q(l,'S'),q(k-l));
    cout << "! " << l << endl;
}   