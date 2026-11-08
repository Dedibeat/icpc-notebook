#import<iostream>
int n,u,R=1,b[32],i;
main() {
    for(std::cin>>n;std::cin>>u;)
        for(i=0;i<32;i++)
            if(u>>i&1)
            if(b[i])
                u ^= b[i];
            else {
                b[i] = u, R *= 2;
                break;
            }
    std::cout<<R;
}
