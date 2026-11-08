#include <bits/stdc++.h>
using l = int64_t;

l M = 1e9 + 7, n, m, k, s;
l p(l a, l b) {
    l r = 1;
    for (; b; b /= 2, (a *= a) %= M) (r *= b % 2 ? a : 1) %= M;
    return r;
}

int main() {
    std::cin >> n >> m;
    for (; k < n; k++) (s += p(m, std::gcd(n, k))) %= M;
    std::cout << s * p(n, M - 2) % M;
}
