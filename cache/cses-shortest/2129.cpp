#include <bits/stdc++.h>
using namespace std;
#define I 1e9
int n,q,d,t;
int main(){
    cin>>n;++n;
    vector<vector<int>> A(n,vector<int>(n));
    for(int i=1;i<n;++i)
        for(int j=1;j<n;++j)
            cin>>A[i][j];
    vector<int> u(n), v(n), p(n), c(n);
    for (int i=1; i<n; ++i) {
    	p[0] = i;
    	int w = 0;
    	vector<int> b (n, I),f (n, 0);
    	do {
    		f[w] = 1;
    		q=p[w];
    		d=I;
    		for (int j=1; j<n; ++j)
    			if (!f[j]) {
    				int m = A[q][j]-u[q]-v[j];
    				if (m < b[j])
    					b[j] = m,  c[j] = w;
    				if (b[j] < d)
    					d = b[j],  t = j;
    			}
    		for (int j=0; j<n; ++j)
    			if (f[j])
    				u[p[j]] += d,  v[j] -= d;
    			else
    	   			b[j] -= d;
    	        w = t;
        } while (p[w]);
        do{
        	t = c[w];
        	p[w] = p[t];
        	w = t;
        } while (w);
    }
    cout<<-v[0];
    for (int i=1; i<n; ++i) cout<<'\n'<<p[i]<<' '<<i;
}