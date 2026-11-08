#include <iostream>

int n, k, a, o[90000];

int main()
{
    std::cin >> n;
    for(k = 1 << n; n--;) printf("1");
    for(n = k/2;--k; o[a -= o[a]] = 1)
        std::cout << o[a = a%n *2 + 1];
}
