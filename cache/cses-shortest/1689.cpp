#include <iostream>

main() {
    int x, y;
    std::string a = "bgJOHE85KPa(74GDfcNIF963QLe`)2C:d_RMB;*1UX]Z+.?<^[VS>A0-WTY\\/,=@";
    std::cin >> x >> y;
    y = a[y * 8 + x - 9];
    for (int p : a)
        std::cout << (p - y + 64) % 64 + 1 << " ";
}
