#import<bits/stdc++.h>
long a,b,c,k,m=2e9;
std::multiset<long> s={1},p;
main(){
    for(;std::cin>>a>>b;)k?p.insert(b*m+a),0:k=b;
    for(long x:p)
        x%m/ *begin(s)&&k++|*s.erase(--s.upper_bound(x%m))||k+~c?s.insert(x/m),c++:0;
    std::cout<<c;
}