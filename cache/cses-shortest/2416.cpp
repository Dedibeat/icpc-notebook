#include <iostream>
using namespace std;
struct pl{long x,y;};
int main()
{
    int n,k;
    cin>>n>>k;
    long x[n+1],y[n+1];
    y[0]=0;
    for(int i=0;i<n;i++)
    {cin>>x[i];
    y[i+1]=y[i]+x[i];
    }
    x[n]=1e9+7;
    pl t[18][n+1];
    t[0][n]={n,0};
    for(int i=n,j;(j=i--);t[0][i]={j,x[i]*(j-i)})
        for(;x[j]<x[i];j=t[0][j].x);
        
    for(int i=1;i<18;i++)
    for(int j=0;j<=n;j++){
        auto [x,y]=t[i-1][j];
        auto [a,b]=t[i-1][x];
        t[i][j]={a,b+y};
    }
    while(k--)
    {
        int a,b;
        
        cin>>a>>b;
        a--;
        long p=y[a]-y[b];
        for(int l=18;l--;){
            auto [x,y]=t[l][a];
            if(x<b){
                a=x;
                p+=y;
            }
        }
        cout<<p+(b-a)*x[a]<<"\n";
        
    }
    
}