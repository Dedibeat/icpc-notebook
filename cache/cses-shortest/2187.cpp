#import <iostream>

typedef int64_t l;
l M = 1e9 + 7,n,k,m,i,H,N,J;

l v(l x) {
    J = 1;
    for(m = 0; m < 31; x = x * x % M)
        if ((M - 2) & (1 << m++))
            J = J * x % M;

    return J;
}

main() {
    char s['   '];

    for (std::cin >> n >> s; s[J] && k >= 0; m += s[J++] == '(')
        k += s[J] - '(' ? -1 : 1;

    N = n % 2 | k < 0 | n / 2 < m;

    n = n / 2 - m;

    for (H = ++k * v(n + k) % M; i < n;)
        H = H * ((n + k + i) * v(++i) % M) % M;

    std::cout << H*!N;
}
