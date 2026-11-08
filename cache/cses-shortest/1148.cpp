#pragma GCC optimize("Ofast,unroll-loops")
#include <cstdio>
#define G getchar()
#define R(i,s,t) for (int i = s; i < t; ++i)

const int N=1001;
int d[N][N],a[N][N];

#include <iostream>
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  G;

  R(i,0,n) {
    R(j,0,m) {
      d[i][j] = 1;
      if (G == '*')
        d[i][j] = 0;
      else if (i)
        d[i][j] = d[i-1][j]+1;
    }
    G;
  }

  R(r,0,n)
    R(i,0,m) {
      int h = d[r][i];
      ++a[h][1];
      R(j,i+1,m) {
        if (h > d[r][j]) h = d[r][j];
        ++a[h][j-i+1];
      }
    }

  R(i,0,n)
    R(j,0,m+1)
      a[n-i-1][j] += a[n-i][j];

  R(i,0,n)
    R(j,0,m)
      printf("%d ", a[i+1][j+1]);
}
