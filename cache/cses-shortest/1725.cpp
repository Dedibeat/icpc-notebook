#include <bits/stdc++.h>
using namespace std;

int n, i, j;
double t;
vector<double> u, v { 1 };

int main () {
    for (cin >> n; n-->0; v = u) {
        u.assign(v.size()+6, 0);
        for (i = 0; i < v.size(); i++)
            for (j = 1; j < 7; j++)
                u[i+j] += v[i]/6;
    }

    for (cin >> i >> j; i <= j; i++)
        t += v[i];

    printf("%.6f", t);
}