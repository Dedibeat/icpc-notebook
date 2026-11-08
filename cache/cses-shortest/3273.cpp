#import<iostream>
 
int r, l, m;
char c,d;
 
main(){
    puts("? 1");
    for (std::cin>>r>>c;l<r-1;m=l+r>>1)
        printf("? %d ",m+1),
        std::cin>>d,
        (c!=d^m%2 ? r : l)=m;
    printf("! %d ",l+1);
}