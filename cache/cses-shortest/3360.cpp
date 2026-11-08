#include <iostream>
#include <bitset>
using namespace std;
int n, k, i, j, h;
string s;
bitset<3001> v[26][3001], c[26];
bool a[26];
int main() {
    cin >> n >> k;
    while (n--) {
        cin >> s;
        for (h = 0; h < 26; ++h) c[h].reset();

        for (j = 0; j < s.size(); ++j) {
            h = s[j] - 'A';
            if (h < k && !a[h]) {
                if ((v[h][j] & c[h]).any()) a[h] = 1;
                v[h][j] |= c[h];
                c[h].set(j);
            }
        }
    }
    for (h = 0; h < k; ++h)
        cout << (a[h] ? "YES\n" : "NO\n");
}
