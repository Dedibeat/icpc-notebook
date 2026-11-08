#include <bits/stdc++.h>
using namespace std;
#define I cin>>a>>b;
#define S [1<<18]

vector<int> g S ,l S; 
int a,b,n,c S,t S;
void f(int i){
    if(!c[i]++){
        for(int j:g[i])
            f(j);
    }
}
void s(int i){
    if(!t[i]++){
        for(int j:l[i])
            s(j);
    }
}
int main()
{
    I
    for(n=a;I l[b].push_back(a))
    g[a].push_back(b);
    s(1);
    for(f(1);n;n--)
    {if(!c[n])
    {printf("NO 1 %d ",n);
    exit(0);
    }
    if(!t[n])
    {printf("NO %d 1",n);
    exit(0);
    }
    }
    puts("YES");
}    
