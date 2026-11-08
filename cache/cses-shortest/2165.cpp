#import<ios>
void h(int k, int s, int d){if(k)h(--k,s,s^d),printf("%d %d ",s,d),h(k,s^d,d);}
main(int n)
{
    printf("%d ",(scanf("%d",&n)<<n)-1);
    h(n,1,3);
}