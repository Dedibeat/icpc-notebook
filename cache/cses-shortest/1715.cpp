#import<ios>
long a,n=1,k=1,i,m=1e9+7,c['  '];
main()
{
    for(;a=getchar()-10;n=n*++i%m)k=k*++c[a]%m;
    for(i=m-2;i;i/=2)n=i&1?n*k%m:n,k=k*k%m;
    printf("%ld",n);
}
