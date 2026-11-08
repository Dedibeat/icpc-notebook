#import<ios>
long c['  '], n,i=1, j,m=1e9+7;
main(){
    scanf("%d",&n);
    for(c[1]=1; i <= n;)
        for(j = ++i; --j; )
            c[j]=(c[j]*j+c[j-1]*(i-j))%m;
 
    for(; ++j <= n;)
        printf("%d ",c[j]);
}