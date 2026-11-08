#import<iostream>
using l= long long;
 
main(){
	l n, k, M = 1e9+7;
	std::cin >> n >> k;
	l dp[2001][1001], a = 0;
	if(k/(n*=2)) k=0,n=0;
	for(l i = 0; i <=n; i++)
		dp[0][i] = 1;
	for(l j = 1; j <= k; j++)
		for(l i = 2; i <=n; i++)
			dp[j][i] = (dp[j][i - 2] + (l) dp[j - 1][i - 2] * ((i - 2) / 4 * 2 + 2 + (i & 1) - j)) % M;
	
	for(l j = 0; j <= k; j++)
		a = (a + dp[j][n] * dp[k - j][n - 1]) % M;
	
	std::cout << a;
}