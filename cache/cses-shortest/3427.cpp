#import<bits/stdc++.h>
using namespace std;
#define y long
struct o{
    y a,b;
    y operator()(y x){
        return a*x+b;
    }
};
#define S (1<<19)
o z;
y n,m,b,j,i;
vector<o> u(2*S);
void w(y i,y a, y d, o l){
    if(i>=2*S)return;
    y s=(a+d)/2;
    if(l(s)>u[i](s))swap(l,u[i]);
    if(l.a<u[i].a)w(2*i,a,s,l);
    else w(2*i+1,s,d,l);
}
main(){
    cin>>n>>m;
    while(n--){
        cin>>b>>j;
        z.a=(j-b)/m;
        z.b=b;
        w(1,0,S,z);
    }
    for(;i<=m;i++){
        y r=0,k=i+S;
        while(k/=2)r=max(r,u[k](i));
        cout << r<<" ";
    }
}