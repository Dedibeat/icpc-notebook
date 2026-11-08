#include <bits/stdc++.h>

long i, l = 3, r = 3, t, z, a[200007];
 
main() {
    std::map<int, int> m;
    while(std::cin>>a[++i]);
 
    while(r < i){
        z += ++m[a[r++]] == 1;
        while(z > a[2]) z -= !--m[a[l++]];
        t += r-l;                       
    }
 
    std::cout<<t; 
}