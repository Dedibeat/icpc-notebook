#import<iostream>
int n, m, i;
main() {
    for (;std::cin >> n >> m;i++ && printf("%d %d ", n < m ? n : m, n < m ? m : n));
}