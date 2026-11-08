#include<bits/stdc++.h>

using namespace std;

int main(){
	int n;
	cin >> n;
	
	int a[n], m = n * (n - 1) / 2, b[m];
	for(int i = 0; i < m; i++)
		cin >> b[i];
	
	sort(b, b + m);
	
	for(int i = 2;; i++){
		a[0] = (b[0] + b[1] - b[i]) / 2;
		
		multiset<int> s;
		for(int i : b)
			s.insert(i);
		
		for(int i = 1; i < n; i++){
			a[i] = *s.begin() - a[0];
			
			for(int j = 0; j < i; j++){
				auto t = s.find(a[i] + a[j]);
				
				if(t == s.end())
					goto f;
				
				s.erase(t);
			}
		}
		
		break;
	f:;
	}
	
	for(int i : a)
		cout << i << " ";
}