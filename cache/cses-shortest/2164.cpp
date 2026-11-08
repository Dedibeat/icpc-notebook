#include <iostream>
int n, k;
main(){
    for(std::cin>>n; std::cin>>n>>k;){
        for(k *= 2; n < k; k = 2*(k-n) - 1);
        printf("%d\n", k);
    }
}