#import<iostream>
int r,i=30;
main(){
    for(char a[4];i--;std::cin>>a,r|=*a%2<<i)
        printf("?%d ",(r|1<<i)-1);
    printf("!%d",r);
}
