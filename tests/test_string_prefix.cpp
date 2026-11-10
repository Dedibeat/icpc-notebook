#include <bits/stdc++.h>
using namespace std;
#include "../sections/string/kmp.cpp"
#include "../sections/string/z_function.cpp"
int main() {
    mt19937 rng(19);
    for (int n = 0; n < 80; ++n) for (int it = 0; it < 40; ++it) {
        string s(n,'a');
        if (it) for (char& c : s) c += rng()%3;
        auto p = prefix_function(s), z = z_function(s);
        assert(p.size() == s.size() && z.size() == s.size());
        for (int i = 0; i < n; ++i) {
            int want = 0;
            for (int k = 1; k <= i; ++k)
                if (s.substr(0,k) == s.substr(i-k+1,k)) want = k;
            assert(p[i] == want);
            want = 0;
            if (i) while (i+want < n && s[want] == s[i+want]) ++want;
            assert(z[i] == want);
        }
    }
}
