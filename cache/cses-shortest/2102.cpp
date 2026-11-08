#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#import <bits/stdc++.h>
using namespace std;
string s;
int i,q;
main(){
    ios::sync_with_stdio(0);
    cin>>s>>q;
    bitset<7<<14>b[130],w;
    for(int c:s)b[c][i++]=1;
    for(;cin>>s;puts(w.any()?"YES":"NO"))
        for(w=b[s[i=0]];++i<s.size();w&=b[s[i]]>>i);
}
