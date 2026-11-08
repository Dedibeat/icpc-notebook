#include<bits/stdc++.h>

using namespace std;

long long n, A, b, i, x[100005], y[100005];

int main(){
	cin >> n;
	for (i = 0; i < n; i++) cin >> x[i] >> y[i];
	x[n] = x[0];
	y[n] = y[0];
	for (i = 0; i < n; i++){
		A += x[i] * y[i+1] - y[i] * x[i+1];
		b += gcd(x[i] - x[i+1], y[i] - y[i+1]);
	}
	cout << (abs(A)-b)/2+1 << " " << b;
}
