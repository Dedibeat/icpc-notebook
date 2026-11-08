#include<cstdio>
#define N 300000
int s[N],a[N],b[N],x[N][99],*n=s,y,z=2,c;
main() {
    a[1]=-1;b[0]=1;
    #define l(t) while(n[-a[t]-1]!=*n)t=b[t];
    while((c=getchar())^10){
        *++n=c;
        l(y)
        if(!x[y][c]) {
            a[z]=a[y]+2,b[z]=b[y];
            l(b[z])
            b[z]=x[b[z]][c];
            x[y][c]=z++;
        }
        y=x[y][c];
        printf("%d ",a[y]);
    }
}
