#import <iostream>
 
int64_t n, m, a[1<<20][20], g[20][20], x, y;
 
main() {
	for(std::cin >> n >> m; std::cin >> x >> y; x = a[1][0] = 1) ++g[x-1][y-1];
 
	for (; x< 1 << n; x+=2)
		for (y=0; ++y < n;)
			for (m = 0; m < n && x & 1<<y;)
				a[x][y] = (a[x][y] + a[x ^ 1 << y][m] * g[m++][y]) % int(1e9+7);
 
	std::cout << a[(1<<n)-1][n-1];
}