#include <bits/stdc++.h>
using namespace std;

int main(){
    long long t, n, r, s, k, q;
    cin>>t;
    while(t--){
        r = 3;
        cin>>n;
        s = sqrt(2*n);
        if(n*2 == s*(s+1)) r = 1;
        if(r != 1) while(--s){
            k = n - s*(s+1)/2;
            q = sqrt(2*k);
            if(k*2 == q*(q+1)) r = 2;
        }
        cout<<r<<endl;
    }
    return 0;
}