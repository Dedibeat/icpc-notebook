#import <bits/stdc++.h>
using namespace std;
 
main(){
    long t, x, y, g;
    for(cin >> t; t--;)
        cin >> x >> y,
        y /= g = gcd(--x, --y),
        cout << x * y * 2 << ' ' << x * y - (x/g - 1) * --y / 2 + 1 << ' ';
}
