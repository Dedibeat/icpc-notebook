#import <iostream>
#define F ;for(i = 0; i < n; i++)
#define C std::cout <<
 
int n, q=10, i, a['   '];
main() {
    std::cin>>n;
    for(char b['   ']; q--;) {
        C "? "
        F C (i>>q&1);
        C ' '; 
        std::cin >> b
        F a[i] |= b[i]%2<<q;
    }
 
    C "! "
    F C -~i[a] << " "; 
}