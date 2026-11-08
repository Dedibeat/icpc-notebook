#import<ios>

long x['  '],t,M=1e9+7,s;
 
main()
{
    for(;s=getchar()-10;x[s]=1+*x)
        *x=t,t=(2*t-x[s]-~M)%M;
    printf("%d",t);
    
}
