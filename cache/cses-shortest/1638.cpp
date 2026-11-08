#import <iostream>
 
int D[1<<20], n, C,M = 1e9+7, I;
char v;
 
main() {
    std::cin >> n;
    for (I = n; std::cin >> v; C=D[I++] = (v>42?I==n?: (D[I-n]+(I%n?D[I-1]:0)):0)%M);
 
    std::cout << C;
}