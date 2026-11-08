#import<bits/stdc++.h>
using namespace std;
int n,k,i,A['   '];
main()
{
    for(cin>>n>>k;cin>>A[i++];);
    multiset s(A,A+k);
    for(auto t=prev(begin(s),~(i=k)/2+1);cout<<" "<<*t,i<n;s.erase(s.find(A[i++-k])))s.insert(A[i]),A[i]<*t?--t:t,A[i-k]>*t?t:++t;
}