#import <bits/stdc++.h>
 
using namespace std;
 
#define E int
#define z .push_front(
#define r [1<<17],
#define P [u]
 
E u, l r k r V;
list<E> a r I;
 
E t(E u, E p) {
    k P = l P = ++V;
 
    for (E v: a P) 
        if (v ^ p && (l P = min(l P, k[v]?:t(v, u))), l[v] > k P)
            I z u), I z v);
    
 
    return l P;
}
 
main() {
    for (cin >> V >> V; cin >> V >> u; a P z V), a[V] z u));
    
    t(1, 1);
 
    I z I.size()/2);
    for (E u : I)
        cout << " " << u;
}