#include<bits/stdc++.h>
using namespace std;
int main(){
    int a,b,x,m,A=0,B=0,t=0,n=0;cin>>a>>b>>x;
    if(x%__gcd(a,b)||x>a)cout<<-1;
    else if(x==a)cout<<1<<" "<<a<<" FILL A";
    else if(x==b&&b<a)cout<<2<<" "<<2*b<<" FILL B MOVE B A";
    else {
        string r;
        while(A!=x){
            if(B==x)swap(A,B),swap(a,b);
            if(!A)A=a,t+=a,r+=" FILL A ",n++;
            if(B==b)B=0,t+=b,r+=" EMPTY B ",n++;
            m=min(A,b-B);
            A-=m;B+=m;t+=m;
            r+=" MOVE A B ",n++;
        }
        cout<<n<<" "<<t<<r;
    }
}
