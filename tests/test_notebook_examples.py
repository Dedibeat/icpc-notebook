"""Compile printed examples and stress the exact printed lazy-tree variants."""
from pathlib import Path
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

def read(name):
    return (ROOT / name).read_text(encoding='utf-8')

def blocks(name):
    return re.findall(r'```cpp\n(.*?)```', read(name), re.S)

template = read('template.cpp').split('void solve()')[0]

with tempfile.TemporaryDirectory() as tmp:
    def run(name, source):
        cpp = Path(tmp) / (name + '.cpp')
        exe = Path(tmp) / name
        cpp.write_text(template + source.replace('int main()', 'signed main()'), encoding='utf-8')
        subprocess.run(['g++', '-std=c++17', '-O2', '-Wall', '-Wextra', str(cpp), '-o', str(exe)], check=True)
        subprocess.run([str(exe)], check=True)
        print(name + ': passed')

    tree = read('sections/data_structures/lazy_segment_tree.cpp')
    examples = blocks('sections/data_structures/lazy_segment_tree.md')
    run('lazy_usage', tree + '\nint main(){\n' + examples[0] + '\nassert(sum==8);}\n')
    for name, config, is_min in [('add_min', examples[1], True), ('assign_sum', examples[2], False)]:
        start = tree.index('    using V =')
        end = tree.index('    // ----------------------------------------------------------------------', start)
        variant = tree[:start] + config + tree[end:]
        main = r'''
int main() {
    mt19937 rng(713);
    SegTree st;
    for(int n=1;n<=35;++n) {
        vector<long long> a(n);
        for(auto& x:a) x=(int)(rng()%101)-50;
        st.init(a); // reuse same object across cases
        for(int it=0;it<1000;++it) {
            int l=rng()%(n+1),r=rng()%(n+1);
            if(l>r) swap(l,r);
            if(rng()%2) {
                long long f=it%5==0?0:(int)(rng()%101)-50;
                st.update(l,r,f);
                for(int i=l;i<r;++i) UPDATE;
            } else {
                long long want=IDENTITY;
                for(int i=l;i<r;++i) AGGREGATE;
                assert(st.query(l,r)==want);
            }
            assert(st.query(1,1)==SegTree::VID);
        }
    }
}
'''
        main = main.replace('UPDATE', 'a[i]+=f' if is_min else 'a[i]=f').replace('IDENTITY', 'LLONG_MAX' if is_min else '0').replace('AGGREGATE', 'want=min(want,a[i])' if is_min else 'want+=a[i]')
        run(name, variant + main)
    example = blocks('sections/data_structures/mo_algorithm.md')[0]
    run('mo_usage', read('sections/data_structures/mo_algorithm.cpp') + '\nint main(){\n' + example + '\nassert((ans==vector<int>{2,3,0}));}\n')

    example = blocks('sections/graph/heavy_light_decomposition.md')[0]
    run('hld_usage', tree + read('sections/graph/heavy_light_decomposition.cpp') +
        '\nint main(){\n' + example +
        '\nassert(pathSum==20 && subtreeSum==10);}\n')

    example = blocks('sections/misc/parallel_binary_search.md')[0]
    run('parallel_bs_usage', read('sections/data_structures/dsu.cpp') +
        read('sections/misc/parallel_binary_search.cpp') +
        '\nint main(){\n' + example +
        '\nassert((ans==vector<int>{0,1,2,3}));}\n')

    example = blocks('sections/data_structures/persistent_segment_tree.md')[0]
    run('pst_usage', read('sections/data_structures/persistent_segment_tree.cpp') +
        '\nint main(){\n' + example +
        '\nassert(sumA==4 && sumB==2 && sumC==11);}\n')

    example = blocks('sections/data_structures/link_cut_tree.md')[0]
    run('link_cut_usage', read('sections/data_structures/link_cut_tree.cpp') +
        '\nint main(){\n' + example +
        '\nassert(a && b && !cycle && sum1==10 && sum2==14 && removed && !joined);}\n')

    automata = blocks('sections/string/automata_usage.md')
    run('aho_usage', read('sections/string/Aho.cpp') + '\nint main(){\n' +
        automata[0] + '\nassert(hits==3);}\n')
    run('eertree_usage', read('sections/string/palindromic_tree.cpp') +
        '\nint main(){\n' + automata[1] +
        '\nassert(represented=="aba" && kinds==5 && copies==2);}\n')
    run('sam_usage', read('sections/string/suffix_automaton.cpp') +
        '\nint main(){\n' + automata[2] +
        '\nassert(has && copies==2 && kinds==9);}\n')

    example = blocks('sections/graph/offline_dynamic_connectivity.md')[0]
    run('offline_connectivity_usage',
        read('sections/graph/offline_dynamic_connectivity.cpp') +
        '\nint main(){\n'
        'vector<long long> values{4,7}, ans(3,-1);\n'
        'vector<int> ask(3,-1); int u=0, v=1;\n' + example +
        '\nassert(t==2); assert((ans==vector<long long>{-1,-1,4}));}\n')

    fps = read('sections/math/ntt.cpp') + '\n' + read('sections/math/formal_power_series.cpp')
    example = blocks('sections/math/formal_power_series.md')[0]
    run('fps_usage', fps + '\nint main(){\n' + example + '\n}\n')

    divisor_sum, tower = blocks('sections/math/counting_formulas.md')
    run('counting_formulas_code', read('sections/math/NT_essentials.cpp') + '\n' +
        divisor_sum + '\n' + tower + r'''
// Independent check: hyperbola method for sum over pairs i*j <= n of i.
long long hyperbola(long long n, long long mod) {
    long long s = sqrtl(n); while ((s + 1) * (s + 1) <= n) s++; while (s * s > n) s--;
    auto T = [&](long long x) { return (long long)((__int128)x * (x + 1) / 2 % mod); };
    __int128 ans = 0;
    for (long long i = 1; i <= s; i++) ans += (__int128)i * (n / i) % mod + T(n / i);
    ans -= (__int128)(s % mod) * T(s);
    return (long long)(((ans % mod) + mod) % mod);
}
int main() {
    const long long M = 1000000007;
    assert(divisor_sum_all(5, M) == 21); // CSES 1082 sample
    vector<long long> sigma(3001);
    for (int d = 1; d <= 3000; d++) for (int k = d; k <= 3000; k += d) sigma[k] += d;
    long long pref = 0;
    for (int n = 1; n <= 3000; n++) pref += sigma[n], assert(divisor_sum_all(n, M) == pref % M);
    mt19937_64 rng(4);
    for (long long n : {1000000000000LL, 999999999999LL, 999966000289LL, 2LL, 3LL})
        assert(divisor_sum_all(n, M) == hyperbola(n, M));
    for (int it = 0; it < 50; it++) { long long n = rng() % 1000000000000LL + 1; assert(divisor_sum_all(n, M) == hyperbola(n, M)); }

    assert(power_tower(3, 7, 1, M) == 2187 && power_tower(15, 2, 2, M) == 50625);
    assert(power_tower(3, 4, 5, M) == 763327764); // CSES 1712 samples
    for (long long p : {2LL, 3LL, 5LL, 7LL, 13LL, M})
        for (long long a = 0; a <= 15; a++) for (long long b = 0; b <= 12; b++) for (long long c = 0; c <= 6; c++) {
            long long e = 1; bool small = true; // exact b^c with 0^0 = 1
            for (int i = 0; i < c && small; i++) e *= b, small = e <= 10000000;
            if (!small) continue;
            long long want = 1 % p; for (long long i = 0; i < e; i++) want = want * (a % p) % p;
            assert(power_tower(a, b, c, p) == want);
        }
}
''')
