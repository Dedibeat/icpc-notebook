#import <bits/stdc++.h>
using namespace std;
 
#define N '   '
long n, t[N*2], s, i, x, y, z, w;
 
 
main(){
    set<array<int, 3>> v;
 
    for(cin>>x; cin >> x >> y >> z >> w; )
        v.insert({z, w += N, i = 2*(x<z) | -2*(x>z) | y<w | -(w<y)}),
        v.insert({x, y += N, -i});
 
    for (auto [a , b, c] : v) {
        for(i = b; i; i -= i & -i) n -= 1/c * t[i];
        for(; b < N*2; b += b & -b) t[b] += c/2;
    }
    cout << n;
}