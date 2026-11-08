#include <iostream>
#define S std::
#define P for(i=0,z=n;i<n;i++)
#define N 1<<19
long n,a[N],b[N],i,c,k,r[4],z;
main(){S cin>>n;P S cin>>a[i];P for(c=k=a[n-i-1],r[3]=z-=c==z;k|c<N;k-=k&-k,c+=c&-c)k?r[0]+=b[k]:0,c<N&&b[c]++;P for(c=i;b[c];b[c]=0,c=a[c-1],r[1]+=c!=i);P c=S lower_bound(b,b+k,a[i])-b,b[c]=a[i],c^k?r[2]++:k++;n=4;P S cout<<r[i]<<' ';}
