"""Stress the exact ShortST machinery with a noncommutative operation."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
s = (root / 'sections/data_structures/short_segment_tree.cpp').read_text()
s = s.replace('using V = long long;', 'using V = string;')
s = s.replace('static constexpr V ID = 0;', 'inline static const V ID = "";')
main = r"""
int main() {
    mt19937 rng(81);
    ShortST t;
    for (int n=0;n<50;++n) {
        vector<string> a(n);
        for(auto& x:a) x=string(1,'a'+rng()%26);
        t.build(a);
        for(int it=0;it<200;++it) {
            if(n) { int p=rng()%n; a[p]=string(1,'a'+rng()%26); t.set(p,a[p]); }
            int l=rng()%(n+1),r=rng()%(n+1); if(l>r) swap(l,r);
            string want; for(int i=l;i<r;++i) want+=a[i];
            assert(t.query(l,r)==want);
        }
    }
}
"""
with tempfile.TemporaryDirectory() as tmp:
    cpp = Path(tmp) / 'ordered.cpp'
    exe = Path(tmp) / 'ordered.exe'
    cpp.write_text('#include <bits/stdc++.h>\nusing namespace std;\n' + s + main)
    subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra',str(cpp),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('ordered ShortST: passed')
