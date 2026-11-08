#import<bits/stdc++.h>

int f(int x, int i)
{
    if(!i)
        return !x;
    for(int r=sqrt(x);r*r*i>=x;r--)
        if(f(x-r*r,i-1))
            {std::cout<<r<<" ";
            return 1;}
    return 0;
}

main()
{
    int n;std::cin>>n;
    while(std::cin>>n)
        f(n,4);
}