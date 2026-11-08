#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const int base = 13331;
string s;
int n, pos = -1;

bool chk(int M) {
    if(s.size() < M) return false;
    ull pre = 0, mul = 1;
    for(int i = 0; i < M; i += 1) {
        pre = pre * base + s[i];
        mul *= base;
    }
    unordered_set<ull> st{pre};
    for(int i = M; i < n; i += 1) {
        pre = pre * base + s[i] - s[i - M] * mul;
        if(st.find(pre) != st.end()) {
            pos = i - M + 1;
            return true;
        }
        st.insert(pre);
    }
    return false;
}

int main() {
    cin >> s;
    n = s.size();

    int L = 0, R = 1e5;
    while(L < R) {
        int M = (L + R + 1) / 2;
        if(chk(M)) L = M;
        else R = M - 1;
    }
    if(!L) cout << -1;
    else cout << s.substr(pos, L);
    return 0;
}
