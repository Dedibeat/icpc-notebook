#import <regex>
std::map<int,long> G['   '],A,B;
int a,b,n;
main(int i) {
    for(;~scanf("%d%d",&a,&b);)n?G[a][b]++:A[n=a]=1;
    if(!B[i]++)
        for(auto[x,y]:G[i])
            main(x),A[i]+=a*y;
    a=A[i]%';��';
    i>1?:printf("%d",a);
}