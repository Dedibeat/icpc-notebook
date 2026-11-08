#pragma GCC optimize"O3,unroll-loops"
#pragma GCC target"avx2"
#import<regex>
int n,c;
main()
{
    std::bitset<'  '>x,y;
    for(;c=~getchar();)x[n++]=c<~48;
    for(y=x;--n-1;printf("%d ",(x&y).count()))y>>=1;
}