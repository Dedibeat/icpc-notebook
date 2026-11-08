#import <iostream>
#define F(n) for (i = 0; i<N&v; ++i) printf("%d ", n+1);
int N, b, n, i, v;
main() {
    for (std::cin >> n; std::cin >> N >> n >> b;) {
        v=printf(n > 0 ^ b > 0 | (n += b) > N?"NO  ":"YES  ");
        F((i < n ? (i + b) % n : i))
        F(i)
    }
}