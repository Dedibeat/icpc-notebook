#include <bits/stdc++.h>
using namespace std;
multiset<int> k;
int n,m;
main(){
	for(cin>>n>>m;cin>>m;k.insert(-1))
	    if(n-->0)k.insert(m);
	    else{
	    	auto i=k.upper_bound(m);
	    	cout<<*--i<<'\n',k.erase(i);
	    }
}
