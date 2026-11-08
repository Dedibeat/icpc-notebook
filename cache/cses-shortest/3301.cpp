#include <bits/stdc++.h>
struct pl{__int128 x,y;};
using namespace std; 
__int128 per[1<<18]={0},bes[1<<18]={0};
int main()
{
    long n,s=0,x;
    cin>>n;
   
    for(int i=0;cin>>x;)
    {
        int j=i++;
        per[i]=s+=x;
        for(int l=bes[j];j&&(s-per[l])*(i-j)>=(s-per[j])*(i-l);l=bes[l])
            j=l;
        bes[i]=j;
        cout<<i-j<<" ";
    }

    return 0;
}