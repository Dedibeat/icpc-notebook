#include <bits/stdc++.h>
using namespace std;
using z=int;
z n;
vector<z> v;
set<z> s;
void f(){
	if(v.size() == n){
		for(z i: v) cout<<i<<" ";
		exit(0);
	}
	for(z i:s){
		if(v.empty() || abs(v.back() - i) > 1){
			v.push_back(i);
			s.erase(i);
			f();
			s.insert(i);
			v.pop_back();
		}
	}
}
z main(){
	cin >> n;
	for(z i=1;i<=n;i++) s.insert(i);
	f();
	cout << "NO SOLUTION";
}