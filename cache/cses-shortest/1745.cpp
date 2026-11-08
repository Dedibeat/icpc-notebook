#import <bits/stdc++.h>
#define S std::
S bitset<'   '> b(1);
int i;
main() {
	for (S cin >> i; S cin >> i;) 
		b |= b << i;
	for (S cout << b.count() - !(i=0) ; ++i < '   '; )
		if (b[i]) S cout << ' ' << i ;
}
