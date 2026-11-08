#import<ext/rope>
int n,k,i,c;
main()
{
    __gnu_cxx::rope<int> r;
    for(scanf("%d%d",&n,&k);i<n;)r+=++i;
    for(;n;r.erase(c,1))printf("%d ",r[(c+=k)%=n--]);
}
