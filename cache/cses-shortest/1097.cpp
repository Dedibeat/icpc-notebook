#include <iostream>
using namespace std;

long long n, s, x[5003], f[5003];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        f[i] = x[i];
        s += x[i];
    }
    for (int i = 1; i < n; i++)
        for (int j = n-1; j >= i; j--)
            f[j] = max(x[j] - f[j-1], x[j-i] - f[j]);
    cout << (s + f[n-1]) / 2;
}
