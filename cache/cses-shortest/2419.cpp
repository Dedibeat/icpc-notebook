#import<iostream>

int i,n,a,s;

main()
{
    for(std::cin>>n;std::cin>>a;)
        s^=n-1-i&i++?0:a;
    std::cout<<s;
}