#import<ios>
main(){int n,x,i=1;scanf("%d",&n);for(;i<=n;){x=2*i++;while(x>n)x=2*(x-n)-1;printf("%d ",x);}}