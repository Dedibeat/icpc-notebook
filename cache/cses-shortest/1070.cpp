#import<ios>
int n,i;
main(){scanf("%d",&n);puts(n<2|n>3?"":"NO SOLUTION");for(i=++n;--i;printf("%d ",i%2*n+i>>1));}
