#import<bits/stdc++.h>
#define S std::
#define W [w]
long n,m,v,y,c='					',a;
S map<int,long> w['		'];
int d(int v){
    n W[v]=1;
    for (auto[k,l]:v W )
        if (!n W [k]&l>=c)
            if(d(k)){
                v W [k]-=c;
                k W [v]+=c;
                return 1;
            }
    return v==n;
}
 
main(){
    for(S cin>>n>>m;S cin>>m>>v>>y;)m==n?:m W [v]+=y;
        for (;d(1)?a+=c:c/=2;n W = *w);
    S cout<<a;
}