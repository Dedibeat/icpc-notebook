#import<iostream>
using namespace std;
int d['   '],m,p,i;
string s,t;
main() {
    for(cin>>s>>t,m=~size(t);s[~i+!i];i=p/m)
        d[++p-m]=p%m*i?min(min(d[p-m],d[p+1])+1,d[p]+(s[~i]!=t[p%m-1])):p%m-i;
    cout<<d[p-m];
}