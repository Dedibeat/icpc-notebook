#import <iostream>

#define S std::

long p = 1e9 + 7, q = 1e7 + 19, a, b, i, n;

main(int o){
    S string s;
    S cin >> s;
    n = s.size();
    for(; ++i < n;){
        a = (a + s[i - 1] * o) % q;
        o = (p * o) % q;
        b = (b * p + s[n - i]) % q;
        if(a == b)
            S cout << i << ' ';
    }
}