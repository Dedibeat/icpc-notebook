#import<regex>
int a,b,n;
std::map<int,int> G['   '],T;
void f(int i) {
    for(auto[x,_]:G[i])
        !T[x]?T[x]=3-T[i],f(x),1:b*=T[x]-T[i];
}
main(){
    for(;!~scanf("%d%d",&a,&b)?++++T[n]/=2,f(n--),n:n?G[a][b],!G[b][a]:n=a;);
    for(;~T[++n+1]/printf(b?"%d ":"IMPOSSIBLE",T[n]););
}