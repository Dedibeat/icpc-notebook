#import<iostream>

int n,i,a,c,h,M=1e9+7,s=1,p['   '],k['   '],f['   '];

#define F ;for(i=1;i<=n;i++)

main()
{
    std::cin>>n
    F
        std::cin>>p[i]
    F
        {for(c=0,a=i;!k[a];c++,a=p[a])
            k[a]=1;
        for(a=2;a<=c;a++)
            for(h=0;!(c%a);h++,f[a]+=h>f[a])
                c/=a;}
    F
        while(f[i]--)
            s=(long long)s*i%M;
    std::cout<<s;
}