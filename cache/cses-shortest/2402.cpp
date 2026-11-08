#include <bits/stdc++.h>
using namespace std;

#define W while(
#define F if(
#define E );
#define N [1<<19],
#define I .insert(
#define Z .size()
#define G .begin()
#define S s[b]

int n, m N u N p=1, d N i, c, a, b;
set<int> s N q;

int f(int x){return d[x] ? f(d[x]) : x;}

main(){
    cin >> n;
    W i < n) s[++i*2] I i E

    W i--){
        cin >> c;
        m[i] = c;

        W q Z && *q G < c){
            W s[b = f(*q G*2)] Z && *S G < p) S.erase(S G E
            q.erase(q G E
            F S Z) F (b = *S G) < c){
                b = f(b*2+1 E
                F s[a = f(c*2)] Z + s[a^1] Z < S Z + s[b^1] Z) swap(a, b E
                F a^b){
                    F (a^b) < 2) return !puts("IMPOSSIBLE" E
                    s[d[b] = a].merge(s[b] E
                    s[d[b^=1] = a^1].merge(S E
                }
            }
            else q I b E
        }
        q I c E
        u[c] = 1;
        W u[p]) p++;
        F s[c = f(c*2+1)] Z) q I *s[c] G E
    }

    W n--) cout << 1 + f(m[n]*2)%2 << ' ';
}
