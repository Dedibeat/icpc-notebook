#include <bits/stdc++.h>
using namespace std;
#define S [1<<18]
std::vector<long> g S ,l S; 
long a,b,c S,t S,o S ,*p=o,k,v S,i,m,n;
void f(long i){
    if(!c[i]++){
        for(long j:l[i])
            f(j);
        *--p=i;
    }
}
long s(long i){
    
    if(!t[i])
    {t[i]=k;long l=v[i];
    for(long j:g[i])
        {
            l+=s(j);
            if(t[j]!=k)
            m=max(m,v[j]);
            
        }
        return l;
    }
    return 0;
}
main()
{
    cin>>a>>b;
    for(p+=n=a;k++<a;cin>>v[k] );
    for(;cin>>a>>b; l[b].push_back(a))
    g[a].push_back(b);
    /*
    1:3
    2:3
    3:6
    4:8,10
    5:7,8,9
    6:1,7
    7:6,9
    8:7,10
    9:8,10
    10:5,6,7,8
    */
    //{1,3,6,7,10,5,8,9},{2},{4}
    while(p-o)
    f(++i);
    //4 2 5 9 10 8 6 7 3 1 
    for(;i=*p++;v[i]=t[i]?v[t[i]]:s(k=i)+m)
        m=0;
    m=0;
    for(long j:v)
    m=max(m,j);
    std::cout<<m;
}