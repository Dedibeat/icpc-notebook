#include <bits/stdc++.h>
using namespace std;  
constexpr int M = 1e9 + 7 , N = 505 ;  
typedef long long LL ;  
LL f[N] , C[N][N] ;  
bool rowA[N], rowB[N] ; 
int a, b , c, limAB,  totA, totB , A[N], B[N] ;  
main(){
  int n ; 
  cin >> n ; 
  for (int i = 0 ; i <= n ; i++) f[0] = C[i][0]  =   1 ;  
  for (int i = 1 ; i <= n ; i++){
    f[i] = f[i-1] * i % M ;
    for (int j = 1 ; j <= n ;j++){
      C[i][j] = (C[i-1][j] + C[i-1][j-1]) % M ; 
      char c ; 
      cin >> c ; 
      if (c == 'A') A[j] =  i, rowA[i] = 1 ; 
      if (c == 'B') B[j] = i, rowB[i] = 1 ;
    }
  } 
  for (int i = 1 ; i <= n ;i++){
    if (!A[i]) {
      totA++ ; 
      a += B[i] && !rowA[B[i]] ; 
    }
 
    if (!B[i]){
      totB++ ; 
      b += A[i] && !rowB[A[i]] ; 
    } 
    c += A[i] + B[i] == 0 ;
    limAB += rowA[i] + rowB[i] == 0 ; 
  }
    LL res = 0 ;
 
  for (int k = 1 ; k <= n; k++){
    LL v = 0 ; 
    for (int i = 0 ; i <= k ;i++){
      for (int j = 0 ; j + i <= k ; j++){
        int l = k - i - j ; 
        if (i <= a && j <= b && l <= min(c, limAB)){
          v += (C[limAB][l] * f[l] % M ) * f[totA-l-i] % M * f[totB-l-j] % M * C[a][i] % M * C[b][j] % M * C[c][l] % M ; 
          v %= M ;
        }
      }
    } 
    res += k & 1 ? -v : v ; 
    res = (res + M) % M ;
  } 
  cout <<  (f[totA] * f[totB] + res ) % M; 
}
