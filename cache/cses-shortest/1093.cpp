#import<iostream>
int x = 1e9+7, n, k, i, j, v[7<<14]={1};
main () {
    for(std::cin >> n,k = n*n+n,i=1; i++<n&!(k&3);)
        for(j=k/4+1; j-->i;)
            (v[j]+=v[j-i])%=x;
    std::cout << (n<2 ? 0 : v[k/4]);
}
