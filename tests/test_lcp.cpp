#include <bits/stdc++.h>
using namespace std;

#include "../sections/string/lcp.cpp"

int main() {
    string s = "banana";
    vector<int> sa = {5, 3, 1, 0, 4, 2};
    vector<int> want = {1, 3, 0, 0, 2};
    assert(lcp_array(s, sa) == want);
    assert(lcp_array("", vector<int>{}).empty());
    assert(lcp_array("aaaa", vector<int>{3, 2, 1, 0}) == vector<int>({1, 2, 3}));
}
