#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

struct T {
    long a = 0, b = -1e18;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long n, m, a, b, l, r, W = 1 << 17;
    auto t = new T[2 * W];

    cin >> n >> m;

    function<void(int, int, int, long, long)> f;
    f = [&] (int i, long u, long v, long a, long b) {
        int m = (u + v) / 2;

        if (l <= u && v <= r) {
            long y = a * m + b, ty = t[i].a * m + t[i].b;

            if (y >= ty) {
                swap(a, t[i].a);
                swap(b, t[i].b);
            }

            if (i < W) {
                if (a < t[i].a)
                    f(i * 2, u, m, a, b);
                else
                    f(i * 2 + 1, m, v, a, b);
            }

            return;
        }

        if (m > l)
            f(2*i, u, m, a, b);

        if (m < r)
            f(2*i + 1, m, v, a, b);
    };

    for (; n > 0; n--) {
        cin >> l >> a >> r >> b;

        a = (b - a) / (r - l);
        b -= a * r;
        r++;

        f(1, 0, W, a, b);
    }

    for (int x = 0; x <= m; x++) {
        b = -1;

        for (int i = 1, j = W / 2; i < 2 * W; j /= 2) {
            b = max(b, t[i].a * x + t[i].b);

            i = 2*i + bool(x & j);
        }

        cout << b << " ";
    }
}
