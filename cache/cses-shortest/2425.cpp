#import <bits/stdc++.h>
using namespace std;

int a, b;
array<int, 3> s['   '], l, r;

main() {
    for (cin >> a; cin >> a >> b; cout << (s[1][2] <= 0 ? "> " : s[1][1] >= 0 ? "< " : "? "))
        for (s[a += '   ' / 2] = {b = 2 * b - 3, b, b}; a /= 2; s[a] = {l[0] + r[0], min(l[1] + r[0], r[1]), max(l[2] + r[0], r[2])})
            l = s[2 * a], r = s[2 * a + 1];
}