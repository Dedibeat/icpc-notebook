#include <iostream>
 
using namespace std;
 
#define f() for (i = y = 0; k = i / P, i < n; ++i)
 
main(){
	int P = 450, n, m, x, y, i, k, a[P*P], b[P];
	cin >> n >> m;
	f() cin >> a[i], b[k] = 2e9;
	for(;m--, cin >> x; cout << y << " ")
		f() i%P || !y * b[k] >= x ? y | a[i] < x ? : (a[y = i] -= x, ++y), b[k] = max(i%P ? b[k] : 0, a[i]) : i += P - 1;
}