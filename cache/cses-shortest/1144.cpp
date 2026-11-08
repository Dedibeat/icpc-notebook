#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define z order_of_key
int n, q, a, b, i;
int main(){
    cin >> n >> q; int v[n];
    tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> s;
    for(; i < n; ++i){
        cin >> v[i];
        s.insert(v[i]);
    }
    while(q--){
        char c; cin >> c >> a >> b;
        if(c == '!'){
            s.erase(s.upper_bound(v[--a]));
            s.insert(v[a] = b);
        }
        else cout << s.z(b + 1) - s.z(a) << '\n';
    }
}