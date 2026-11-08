#include<bits/stdc++.h>
using namespace std;
int n, k, i, j;
#define f(i,n) for(i = 1; i <= n; i ++){
long d[3001][3001],a[26];
main(){
    cin>>n>>k;
    string v[n + 1];
    f(i,n)
        cin>>v[i];
        v[i] = " " + v[i];
    }
    f(i,n) f(j,n)
        char c = v[i][j];
        a[c - 'A'] += d[i][j] = 1 + (c == v[i - 1][j] & c == v[i][j - 1] & c == v[i - 1][j - 1] 
                ? min({d[i - 1][j], d[i][j - 1], d[i - 1][j - 1]}) 
                : 0);
        }
    }
    i=0;
    while(i<k)
        cout<<a[i++]<<" ";
}
