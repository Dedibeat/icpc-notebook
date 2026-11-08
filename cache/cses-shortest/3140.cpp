#include <iostream>
int64_t v;
#define q(i,j) ;if(v && j) {printf("%d %d\n", i, j);std::cin >> v;}
main() {
  std::cin >> v
  q(1, 1)
  for (int i = 2; v; i++) {
    auto c = v
    q(1, i)
    q(2, i)
    c = (i-c+v)/2
    q(1, c+1)
    q(1, c)
  }
}
