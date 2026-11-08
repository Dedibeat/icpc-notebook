#import<bits/stdc++.h>
double s, i, n, k;
main() {
    for (std::cin >> n >> k, s = i = k;--i;)s -= pow(i / k, n);
    printf("%f", s);
}