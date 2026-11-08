#import <iostream>
long a,i = '   ',j,h['   '], A['   '];
main() {
    for (;std::cin>>a;)j++&&++h[a];
    for (;i; A[i--] -= a*~a/2)
        for (a = j = 0; j<'   '; j += i) a -= h[j],A[i] -= A[j];
    std::cout << A[1];
}