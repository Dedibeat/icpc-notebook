"""Compile printed examples and stress the exact printed lazy-tree variants."""
from pathlib import Path
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

def read(name):
    return (ROOT / name).read_text()

def blocks(name):
    return re.findall(r'```cpp\n(.*?)```', read(name), re.S)

with tempfile.TemporaryDirectory() as tmp:
    def run(name, source):
        cpp = Path(tmp) / (name + '.cpp')
        exe = Path(tmp) / name
        cpp.write_text('#include <bits/stdc++.h>\nusing namespace std;\n' + source)
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
            int l=rng()%n,r=rng()%n;
            if(l>r) swap(l,r);
            if(rng()%2) {
                long long f=it%5==0?0:(int)(rng()%101)-50;
                st.update(l,r,f);
                for(int i=l;i<=r;++i) UPDATE;
            } else {
                long long want=IDENTITY;
                for(int i=l;i<=r;++i) AGGREGATE;
                assert(st.query(l,r)==want);
            }
            assert(st.query(1,0)==SegTree::VID);
        }
    }
}
'''
        main = main.replace('UPDATE', 'a[i]+=f' if is_min else 'a[i]=f').replace('IDENTITY', 'LLONG_MAX' if is_min else '0').replace('AGGREGATE', 'want=min(want,a[i])' if is_min else 'want+=a[i]')
        run(name, variant + main)
    example = blocks('sections/data_structures/mo_algorithm.md')[0]
    run('mo_usage', read('sections/data_structures/mo_algorithm.cpp') + '\nint main(){\n' + example + '\nassert((ans==vector<int>{2,3,0}));}\n')

    example = blocks('sections/data_structures/persistent_segment_tree.md')[0]
    run('pst_usage', read('sections/data_structures/persistent_segment_tree.cpp') +
        '\nint main(){\n' + example +
        '\nassert(kthValue==2); assert(count==2);}\n')

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
        '\nint main(){\n' + example +
        '\nassert(q0==0 && q1==1 && q2==2 && q3==3); '
        'assert((ans==vector<char>{1,0,1,0}));}\n')

    fps = read('sections/math/ntt.cpp') + '\n' + read('sections/math/formal_power_series.cpp')
    example = blocks('sections/math/formal_power_series.md')[0]
    run('fps_usage', fps + '\nint main(){\n' + example + '\n}\n')
