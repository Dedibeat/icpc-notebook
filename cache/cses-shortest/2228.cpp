#import <iostream>

long n, k, A, C = 1, i, p;
int const M = 1e9+7;
int P(int e) {
    p = e?P(e/2):1;
    return p*p%M*(e&1?i:1)%M;
}

main() {
    for (std::cin >> n >> k; ~k;
        C = C * k-- % M * P(M-2) % M)
        A += C * (k&1?M-1:1) % M * P(n) % M, ++i;
    std::cout << A%M;
}
