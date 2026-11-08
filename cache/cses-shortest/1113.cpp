#import <bits/stdc++.h>

using namespace std;

main(){
    string s; cin >> s;
    int n = size(s), v[n];
    iota(v, v+n, 0);
    stable_sort(v, v+n, [&](int i, int j) { return s[i] < s[j]; });
    for (n=*v; n;)
        cout << s[n = v[n]];
}