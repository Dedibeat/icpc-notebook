#import<iostream>
long n, k, x, b, c, d, a ,i;
main() {
    for ( std::cin >> n >> k >> x >> b >> c >> d; i < n; x = (x * b + c) % d)
        a ^= std::min({n-i, ++i, k}) % 2 * x;
    std::cout<<a;
}