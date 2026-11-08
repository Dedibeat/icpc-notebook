#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> cd;
const double PI=acos(-1);
const int B=19;
const int N=1<<B;

int r[N];
cd a[N], b[N];

int rev(int x) {
	int ans=0;
	for(int i=0; i<B; i++) {
		ans=ans*2+x%2;
		x/=2;
	}
	return ans;
}

void FFT(cd *x, int f) {
	for(int i=0; i<N; i++)
		if(i<r[i])
			swap(x[i], x[r[i]]);
	for(int d=1; d<N; d*=2) {
		cd w0=polar(1.0, f*PI/d);
		for(int i=0; i<N; i+=2*d) {
			cd w=1;
			for(int j=i; j<i+d; j++, w*=w0) {
				cd t1=x[j]+w*x[j+d];
				cd t2=x[j]-w*x[j+d];
				x[j]=t1;
				x[j+d]=t2;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for(int i=0; i<N; i++)
		r[i]=rev(i);
	string s;
	cin >> s;
	int n=s.size();
	a[0]=b[n]=1;
	for(int i=1, t=0; i<=n; i++) {
		t+=(s[i-1]=='1');
		a[t]+=1;
		b[n-t]+=1;
	}
	FFT(a, 1);
	FFT(b, 1);
	for(int i=0; i<N; i++)
		a[i]*=b[i]*(1.0/N);
	FFT(a, -1);
	a[n]=(a[n]-cd(n+1))*0.5;
	for(int i=n; i<=2*n; i++)
		cout << ll(real(a[i]+0.5)) << " \n"[i==2*n];
	return 0;
}