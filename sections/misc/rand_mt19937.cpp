#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    int x = rng();               // random 32-bit integer
    int y = rng() % 100;         // 0 to 99
    cout << x << " " << y << "\n";
}
