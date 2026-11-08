#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int main() {
  int n;
  cin >> n;
  vector<int> A(n), st{INF}, D;
  for (int &a : A) cin >> a;
  sort(begin(A), end(A));
  for (int i = 0; i < n - 1; i++) A[i] = A[i + 1] - A[i];
  A[n - 1] = INF;
  for (int a : A) {
    while (st.size() > 1 && st.back() <= st[st.size() - 2] && st.back() <= a) {
      int b = st.back();
      st.pop_back(), D.push_back(b);
      a += st.back() - b, st.pop_back();
    }
    st.push_back(a);
  }
  sort(begin(D), end(D));
  long long s = 0;
  for (int d : D) printf("%lld ", s += d);
  return 0;
}