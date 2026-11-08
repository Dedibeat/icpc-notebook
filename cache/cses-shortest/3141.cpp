#include<ios>
constexpr int S =1<<18,M=1e9+7;
long s[S],n,t,j=1,i;
#define I(N) scanf("%d",&N)
int main()
{
    for(int i=0;i<S;i++)
    s[i]=1;
    for(I(n);~I(t);)
    s[S-1-t]=(s[S-1-t]<<1)%M;
    for(;j<S;j<<=1)
    for(i=0;i<S;i++)
    if(j&i)
    s[i]=(s[i]*s[j^i])%M;
    for(j=1;j<S;j<<=1)
    for(i=0;i<S;i++)
    if(j&i)
    s[i]=(M+s[i]-s[j^i])%M;
    
    for(int i=0;i<=n;i++)
        printf("%d ",s[S-1-i]);
}