#import <iostream>
int D['   '], x, v, j, m = 1e9 + 7;
main()
{
  std::cin >> x >> x;
  for (*D = 1; std::cin >> v;)
    for (j = v; j <= x; j++)
      (D[j] += D[j - v]) %= m;
  std::cout << D[x];
}