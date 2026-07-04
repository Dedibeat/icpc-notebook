#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    unsigned x = rng();           // random 32-bit (int x = rng() can be negative!)
    int y = rng() % 100;          // 0..99, slight modulo bias (fine for CP)
    int z = uniform_int_distribution<int>(5, 10)(rng); // exact uniform in [5,10]
    long long big = ((long long)rng() << 31) ^ rng();  // or use mt19937_64
    vector<int> v = {1, 2, 3};
    shuffle(v.begin(), v.end(), rng); // NEVER random_shuffle (uses rand())
    cout << x << " " << y << " " << z << " " << big << "\n";
}
