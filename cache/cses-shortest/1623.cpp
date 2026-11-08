#import <iostream>
using namespace std;
int w[21],n;
long f(int k, long s){
    return k--?min(f(k,s+w[k+1]), f(k,s-w[k+1])):abs(s);
}
main(){
    while(cin>>w[n++]);
    cout<<f(n-1, 0);
}