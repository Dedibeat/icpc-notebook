#import<regex>
int n,i,d,I,J;
main(){for(scanf("%d",&n);i<n*n;++i)I=i/n,J=i%n,I>J?:I^=J^=I^=J,d=std::max(-~I/2,(I+J+2)/3),printf("%d ",I+J==1?3:I^J||!J|J>2?n^4||I^3|J?d+(d+I+J)%2:5:4);}