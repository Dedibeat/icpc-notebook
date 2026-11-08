#import <iostream>
int n,u,s;
main() {
    for(;std::cin>>u;) s ^= n++^u;
    std::cout<<s;
}

