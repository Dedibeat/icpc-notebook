#import<bits/stdc++.h>
using namespace std;
#define B .begin()
#define I (X[i
long n,k,s,i;
main(){
	cin>>n>>k;
	vector<int>X(n);
	for(int&x:X)cin>>x;
	multiset<int>S(X B,X B+k);
	auto t=next(S B,-~k/2-1),u=t;
	for(;i<k;i++)s+=abs I]-*t);
	for(cout<<s;i<n;i++){
		S.insert I]);
		if I]<*t)t--;
		if I-k]<=*t)t++;
		S.erase(S.find I-k]));
		s+=abs I]-*t)-abs I-k]-*u)+~k%2*(*t-*u);
		cout<<" "<<s;
		u=t;
	}
}