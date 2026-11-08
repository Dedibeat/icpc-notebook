#include <iostream>
using std::cin;

#define z int
#define F for(
const z b=2e6;
z u[b][31], w[b], t[b], i=1, n,q,x,y,p;
 
z d(z x){
    if(!t[x])
    t[x] = 1,d(u[x][0]),w[x] = 1 + w[u[x][0]];
}
 
z l(z x, z k){
    if(k<0) return 0;
    F i=0;i<31;i++)
        if(k&(1<<i)) x = u[x][i];
    return x;
}

main(){
    cin >> n >> q;

    F ;i<=n;) cin >> u[i++][0];
 
    F i=1;i<31;i++)
        F p=1;p<=n;p++)
            u[p][i] = u[u[p][i-1]][i-1];
    
    F i=1;i<=n;i++) if(!t[i]) d(i);
 
    F ;cin>>x>>y;){
        p = l(x, w[x]), n=w[x]-w[y];
        printf("%d\n",l(x,n)==y?n:l(p, w[p]-w[y])==y?n+w[p]:-1);
    }
}