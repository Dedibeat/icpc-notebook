#import <bits/stdc++.h>
using namespace std;
int n,i,x,y,d,a['   '];
multimap< int,pair<int,int> > m;
main(){
    for(cin >> n;cin >> x >> y;m.insert({x,{y,i++}}));
    for(auto t=m.begin();i=!m.empty();t==m.end()?t=m.begin(),++d:0){
	    auto b=(*t).second;
	    m.erase(t);
	    a[b.second]=d;
	    t=m.upper_bound(b.first);
    }
    for(cout << d << ' ';i<n;cout<<a[i++]+1<< ' ');
}
