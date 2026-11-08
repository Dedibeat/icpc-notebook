#include<iostream>

main(){
	long long k,i= 1, n , s=0 , p = 2e9+14;;
	std::cin >> n;
	for(; i*i <= n; i ++){
		k = n/i;
		s =(s + (((k + i) % p) * ((k+i) % p)) % p - (4*i*i)%p + k + i + p)%p;
	}
	std::cout << s/2;


}

