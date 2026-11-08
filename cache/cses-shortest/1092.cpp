#include <iostream>
auto& c = std::cout;

int main() {
    int n, i{};
    std::cin >> n;
    if (++n & 2)
        c << "NO";
    else {
        c << "YES " << n-- / 2 << ' ';
        while(n - i++)
            if (i - n & 2)
                c << i << ' ';
        c << n-- / 2 << ' ';
        while (--i)
            if (n - i & 2)
                c << i << ' ';
    }
}