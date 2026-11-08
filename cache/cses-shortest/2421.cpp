#import<iostream>
#define x o[k]
long d[30][5011], c[5011][5011], n, o[50], p, q, i, j, k, m = 1e9 + 7;
std::string s;
int main() {
	std::cin >> s;
	n = s.size();
	for(i = 0; i < n; i++) o[s[i] - 96]++;
	for(i = c[0][0] = d[0][0] = 1; i <= n; i++) 
		for(j = c[i][0] = 1; j <= n; j++) 
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j])%m;
	for(k = 1; k <= 26; k++) {
		if(!x) continue;
		for(i = 0; i <= q; i++) 
			for(j = 1; j <= x; j++)
				d[k][i + j] = (d[k][i + j] + d[p][i] * c[i + j][j]%m * c[x - 1][j - 1]%m)%m;	
		p = k;
		q += x;
	}
	for(i = 1; i <= n; i++) 
		d[p][i] = (d[p][i] - d[p][i - 1] + m)%m;
	std::cout << d[p][n]; 
}
