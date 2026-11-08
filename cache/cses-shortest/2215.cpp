#import "iostream"

main()
{
    int n,k,j; std::cin>>n;
    while (std::cin>>n>>k)
        if (k*k<n) puts("IMPOSSIBLE");
        else
        for (;n>0;)
            for (j=0>(n-=k)?0:n;j<n+k;)
                printf("%d ",++j);

}
