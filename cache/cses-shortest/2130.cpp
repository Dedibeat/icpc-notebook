#include<bits/stdc++.h>
#define breturn return
using namespace std;
struct edge {
	int f, t, c, r, w;
};
edge e[2420];
int n, m, k, a, b, o, d[569], p[569];
vector<int> v, g[569];

int main() {
	cin >> n >> m >> k;
	for(int i = 0; i < 2 * m; i+=2) {
		cin >> a >> b;
		e[i].f = a;
		e[i].t = b;
		e[i].c = 1;
		e[i].w = 1;
		e[i].r = i + 1;
		g[a].push_back(i);
		e[i + 1].f = b;
		e[i + 1].t = a;
		e[i + 1].c = 0;
		e[i + 1].w = -1;
		e[i + 1].r = i;	
	}
	b = k;
	while(1) {
		for(int i = 2; i <= n; i++) d[i] = 1e9;
		for(int i = 0; i < n - 1; i++) 
			for(int j = 0; j < 2 * m; j++) 
				if(e[j].c && d[e[j].t] > d[e[j].f] + e[j].w) 
					d[e[j].t] = d[e[j].f] + e[j].w, p[e[j].t] = j;
		if(d[n] > 1e8) 
			break;
		o += d[n];
		for(a = n;a - 1; a = e[p[a]].f) {
			e[p[a]].c--;
			e[e[p[a]].r].c++;
		}		
		k--;	
		if(!k) 
			break;
	}
	if(k)
		breturn cout << -1, 0;
	cout << o << '\n';
	for(int i = 0; i < b; i++) {
		a = 1;
		while(a != n) {
			v.push_back(a);
				for(int i = 0; i < g[a].size(); i++) 
					if(!e[g[a][i]].c) {					
					e[g[a][i]].c = 1;
					a = e[g[a][i]].t;
					break;
			}		
		}
		v.push_back(n);
		cout << v.size() <<'\n';
		for(auto t:v) 
			cout << t <<" ";
		cout << '\n';
		v.clear();		
	}
}
