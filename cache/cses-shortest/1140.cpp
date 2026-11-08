#include<bits/stdc++.h>
using namespace std;
main(){
int N;
cin>>N;
map<int,int64_t>m;
m[0]=0;
array<int,3>A[N];
for(int i=0;i<N;i++)cin>>A[i][1]>>A[i][0]>>A[i][2];
sort(A,A+N);
int64_t c=0;
for(int i=0;i<N;i++)m[A[i][0]]=(c=max(c,prev(m.lower_bound(A[i][1]))->second+A[i][2]));
cout<<c;
}
