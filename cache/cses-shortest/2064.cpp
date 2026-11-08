#include <iostream>
 
using l = long long;
 
l M = 1e9 + 7;
 
l b(l a, l n)
{
    l r = 1;
    while(n){
        if (n % 2) r = (r * a) % M;
        a = (a * a) % M;
        n /= 2;
    }
    return r;
}
 
int main(){
    l n;
    std::cin >> n;
    l c = ~n & 1;
    for (l i = 1; i <= n / 2; ++i) c = c * (4 * i - 2) % M * b(i + 1, M - 2) % M;
    std::cout << c;
}
 