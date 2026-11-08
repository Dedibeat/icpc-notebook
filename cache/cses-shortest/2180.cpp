#include <iostream>
using namespace std;
main(){
    long n, c = 0, t = 0, a, i=0; cin>>n;
    int u[n];
    for(int &p: u) cin>>p;
    while(cin>>n) c += u[i++]-1, t += n-1, a += abs(c + t), a += n = c*t<0 ? min(abs(c), abs(t)) : 0, c += n = c>0 ? -n : n, t -= n;
    cout<<a;
}