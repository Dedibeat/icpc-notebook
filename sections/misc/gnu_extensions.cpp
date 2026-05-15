#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// NOTE: examples below are not one compilable file; paste only the needed block.
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

template<typename K, typename V>
using ordered_map = tree<
    K,
    V,
    less<K>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

ordered_set<int> s;

s.insert(x);
s.erase(x);

// number of elements strictly smaller than x
int k = s.order_of_key(x);

// iterator to k-th (0-indexed) element
auto it = s.find_by_order(k);

using pii = pair<int,int>;

ordered_set<pii> ms;
int id = 0;

ms.insert({value, id++});

// erase one occurrence
ms.erase(ms.lower_bound({value, 0}));

tree<int, null_type, less_equal<int>,
     rb_tree_tag,
     tree_order_statistics_node_update> ms;

#include <ext/rope>
using namespace __gnu_cxx;

rope<char> r;

r.insert(pos, "abc");
r.erase(pos, len);
r.replace(pos, len, "xyz");

char c = r[i];
