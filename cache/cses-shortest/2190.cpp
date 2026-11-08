#include "bits/stdc++.h"
using namespace std;
#define f(a, b, c, d) ((a)*(d)-(b)*(c))

int main(){
 double t, A, a, B, b, C, c, D, d;
 for(cin >> t; cin >> A >> a >> B >> b >> C >> c >> D >> d;)
  puts(f(D-A, d-a, B-A, b-a) * f(B-A, b-a, C-A, c-a) >= 0 & f(B-C, b-c, D-C, d-c) * f(D-C, d-c, A-C, a-c) >= 0 & (f(C-A, c-a, B-A, b-a) || f(D-A, d-a, B-A, b-a) || !(min(a+=A*2e9, b+=B*2e9) > max(c+=C*2e9, d+=D*2e9) | max(a, b) < min(c, d)))? "YES" : "NO");
}
