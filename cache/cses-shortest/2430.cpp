#import<iostream>
int n,u,j,i=0,m=99;
int c(int a, int b){ return a^b ? b/(a+1) + c(b%(a+1),a) : a ? m : b; }
main(){
    std::cin>>n;
    for(;i*2 < n;++i) if((u=c(i,n-i)) < m)m=u,j=i;
    for(n-=j;n+j;)
        if(n>j) n -= j+1, putchar('1');
        else j -= n+1, putchar('0');
}