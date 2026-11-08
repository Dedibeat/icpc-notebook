#import <bits/stdc++.h>
#define S [1<<16]
#define I std::cin>>a>>b
#define w for(
std::vector<int> g S ,l S ;
std::bitset<50002> r S ;
int n,m,a,b,c S ,t S ,o S,*p=o;
void f(int i){
    if(!c[i]++){
        w int j:l[i])
            f(j);
        *--p=i;
    }
}
void k(int i){
    if(!t[i]){
        t[i]=a;
        w int j:g[i])
        {k(j);
        r[i]|=r[j];
        }
    }
}
main()
{
    I>>n;
    w p+=n=a,m=b;m--;g[a].push_back(b),l[b].push_back(a))
    I;
    w ;n;r[n][n--]=1)
    f(n);
    w ;a=*p++;r[a]=r[t[a]])
    k(a);
    w ;I;)
    puts(r[a][b]?"YES":"NO ");
}    
