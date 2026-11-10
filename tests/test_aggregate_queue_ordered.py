"""Stress the exact AggQueue machinery with order-sensitive and non-idempotent ops."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
base = (root / 'sections/data_structures/aggregate_queue.cpp').read_text(encoding='utf-8')
DEFAULT = ['using V = long long;', 'static constexpr V ID = 0;',
           'static V op(V a, V b) { return gcd(a, b); }']
for line in DEFAULT:
    assert base.count(line) == 1, line

VARIANTS = {
    # Concatenation: any order mistake changes the string.
    'concat': (['using V = string;', 'inline static const V ID = "";',
                'static V op(V a, V b) { return a + b; }'],
               'string', 'string(1, char(\'a\' + rng() % 26))',
               'string want; for (auto& x : d) want += x;'),
    # Affine maps x -> a*x + b mod P, applied front first.
    'affine': (['using V = pair<long long, long long>;', 'inline static const V ID = {1, 0};',
                'static V op(V f, V g) { return {f.first * g.first % 1000003, '
                '(g.first * f.second + g.second) % 1000003}; }'],
               'pair<long long, long long>', 'pair<long long, long long>(rng() % 1000003, rng() % 1000003)',
               'pair<long long, long long> want{1, 0};'
               ' for (auto& g : d) want = {want.first * g.first % 1000003,'
               ' (g.first * want.second + g.second) % 1000003};'),
    # Sum is not idempotent, so double-counting shows up.
    'sum': (['using V = long long;', 'static constexpr V ID = 0;',
             'static V op(V a, V b) { return a + b; }'],
            'long long', '(long long)(rng() % 2001) - 1000',
            'long long want = 0; for (auto x : d) want += x;'),
}

MAIN = r"""
int main() {
    mt19937 rng(SEED);
    AggQueue q;
    for (int round = 0; round < 200; round++) {
        deque<TYPE> d;
        int pushBias = 1 + rng() % 4;
        for (int it = 0; it < 300; it++) {
            if (d.empty() || (int)(rng() % (pushBias + 1)) != 0) { TYPE x = MAKE; q.push(x), d.push_back(x); }
            else q.pop(), d.pop_front();
            BRUTE
            assert(q.size() == (int)d.size() && q.query() == want);
        }
        while (!d.empty()) q.pop(), d.pop_front();
        assert(q.size() == 0 && q.query() == AggQueue::ID);
    }
}
"""

with tempfile.TemporaryDirectory() as tmp:
    for seed, (name, (lines, typ, make, brute)) in enumerate(VARIANTS.items(), start=11):
        s = base
        for old, new in zip(DEFAULT, lines):
            s = s.replace(old, new)
        main = MAIN.replace('SEED', str(seed)).replace('TYPE', typ).replace('MAKE', make).replace('BRUTE', brute)
        cpp = Path(tmp) / f'{name}.cpp'
        exe = Path(tmp) / f'{name}.exe'
        cpp.write_text('#include <bits/stdc++.h>\nusing namespace std;\n' + s + main, encoding='utf-8')
        subprocess.run(['g++', '-std=c++17', '-O2', '-Wall', '-Wextra', '-D_GLIBCXX_ASSERTIONS',
                        str(cpp), '-o', str(exe)], check=True)
        subprocess.run([str(exe)], check=True)
        print(f'aggregate queue {name}: passed')
