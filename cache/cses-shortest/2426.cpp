#include<bits/stdc++.h>

using namespace std;
array<int, 2> d[1 << 18];
int64_t v[1 << 18];


int main() {

    int a, b, n;
    cin >> a >> b >> n;
    for (int i = 0; i < n; i++) cin >> d[i][0] >> d[i][1];
    sort(d, d + n, greater<>());
    int64_t w = 0;
    priority_queue<int> q;
    for (int i = 0; i < a + b; i++) {
        w += d[i][0];
        q.push(d[i][1] - d[i][0]);
        if (i >= a) {
            w += q.top();
            q.pop();
        }
        v[i + 1] = w;
    }
    w = 0;
    while (!q.empty()) q.pop();
    for (int i = n - 1; i >= a; i--) {
        q.push(d[i][1]);
        if (i <= a + b - 1) {
            w += q.top();
            q.pop();
            v[i] += w;
        }
    }
    cout << *max_element(v, v + n + 1);

}
