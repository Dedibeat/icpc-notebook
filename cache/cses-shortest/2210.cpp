#import <iostream>
typedef long l;
l m = 1e9 + 7;
l d = 25e7 + 2;

l p(l n) {
	l r = 1;
	for (l x = 2; n; n /= 2, x = x * x % m)
		if (n & 1) r = r * x % m;
	return r;
}

main() {
	l n; std::cin >> n; l N = n * n;
	std::cout << (p(N) + 2 * p((N + 3) / 4) + p((N + 1) / 2)) * d % m;
}