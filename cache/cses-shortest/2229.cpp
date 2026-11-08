#import <iostream>
long n, k, M = 1e9+7, s, t, i, j;
main(){
	std::cin >> n >> k;
	long d[n*n]={1};
	for(; i++ < n;)
		for(s = 1, j = i * (i - 1) / 2; j >= 0; j--)
			t = d[j], d[j] = s, s = (s + (j >= i)*d[j - i] - t + M) % M;
	std::cout << d[k];
}