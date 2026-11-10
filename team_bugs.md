# Team bug evidence for the debug checklist

Source for [sections/misc/debug.md](sections/misc/debug.md) and the
[stress-test exercises](practice/stress/README.md). Data: sibling repo `analyze_standings`
(`data/team_r3/submissions.json`, `data/team_r3/code/`, `members_solved.csv`, and the coach review
`output/team_r3_coach/{summary,cf}.md` with one dossier per contest). Fourteen TEAM_R3 virtuals,
2026-08-20 to 2026-11-01, 179 submissions. Members come from `members_solved.csv` joined to the
submissions by problem; 31 solves have no member (1051, 1485, 2513, 2524, 2575).

## Where the penalty goes

68 penalised wrong runs = 1360 minutes, about 97 per contest. In 5 of the 9 regional/CCPC virtuals,
penalty alone moved us across a medal or EC-Final line. Chengdu 2026 missed gold by 59 minutes;
C's wrong modulus and D's overflow cost 60.

| class | runs | examples |
|---|---|---|
| unproven idea / greedy / guessed formula | 14 | 4607 D, 2524 C x3, 1053 A x2, 2661 B, 1051 E, 1799 L |
| casework / off-by-one | 11 | 2693 F x2, 2661 M, 1794 G, 1794 F |
| memory or time not estimated | 10 | 1485 G x3, 1485 D x2, 2575 J x2, 1799 L, 1799 G |
| data-structure misuse | 8 | 2661 G max-heap, 2524 J `map[]` while iterating, 2513 M |
| edge parameters and indexing | 7 | 4593 J size n indexed to 2n, 1053 E k = n, 2661 B p = 0 |
| blind or identical resubmission | 6 | 1799 L identical, 2661 G toggles, 1794 G `#define int long long` |
| overflow / sentinel / modular | 5 | 4607 D `b * (k + 4)`, 4593 C INF, 2575 L `inf + 1`, 1071 A |
| debug leftovers and typos | 4 | 1071 G `cnt = 100`, 1485 G DSU typo, 1096 L `%.10.lf` |
| misread statement constant | 3 | 4607 C modulus 1e9+7 vs 998244353 |

## Per member (in-contest runs on problems the member owned)

| | Dedi | Erdene | Tamir |
|---|---|---|---|
| runs / AC | 45 / 18 | 33 / 17 (+2 AC,WA) | 14 / 8 |
| rejected | 27: WA 19, TL 4, RE 3, ML 1 | 13 WA | 6 WA |
| on never-solved problems | 11 (4607 E 5, 1053 C 2, 1071 M 2, 2661 J 2) | 0 | 0 |
| CF first-try AC | 68% | 78% | 78% |
| CF rejections failing test 1 | **38%** | 28% | 19% (41% in CF-rules rounds) |

Pair problems add 8 more rejected runs: 1794 L x4 (Dedi's idea, Tamir's code; GPT-assisted),
1071 G x2 and 1053 A x2 (Tamir's idea, Dedi's code).

**Dedi** -- implementation details on problems with a right idea, plus unchecked runs:
- constants and sentinels: 4607 C `const int mod = 1e9 + 7` in 3334409 and 3334633
  (statement: 998244353); 4593 C INF below real answers; 4593 J `int f[N]` indexed to 2n (3274161);
- leftovers: 2661 J `for(int l = 0; l < 3; l++)` in 3192839, one character from AC (#127 -> #86);
- casework: 2693 F inverted boolean (3152894), then a missing branch (3153295); 2661 M lexicographic
  `max` on binary strings (3191371);
- identical resubmission: 1799 L 2924110 = 2924396 byte for byte; 1071 M 3081379;
- cost not estimated: 1799 G exponential recursion (ML), 1799 L gcd inside binary search (TL),
  1053 C knapsack rebuilt per child (TL);
- unproven idea: 4071 A x4 in the official round, Erdene then AC first try;
- CF: 237 of 630 rejections fail test 1; 2196 C1 nine idleness runs (no flush).

**Erdene** -- wrong models and data-structure details, few runs overall:
- 4607 D: two wrong models (3333931, 3334026), then `ha - b * (k + 4)` overflow (3334250);
- 2661 G: wrong idea, then `priority_queue<..., less<...>>` max-heap (3191724), then toggles
  (3191747-3191819);
- 1794 G: median definition (2801138), then a blind `#define int long long` (2801280);
- 1096 C symmetric case (3136338); 1096 L `printf("%.10.lf")` (3137798); 1071 D unproven (3078780);
- setup: 139 of 348 CF submissions in 2026 on 32-bit GCC 7 (no `__int128`).

**Tamir** -- cleanest first runs; fails on hidden degenerate cases:
- 1794 F: equal values double-counted, `<` on both monotonic stacks (2800660);
- 2661 B: no global equal-count check (3191526, 3191627), then p = 0 / q = 0 leaves a group list
  empty (3192234, 3192623, 3192772): 169 minutes, 5 WA.

## Process facts behind the shared rules

- Testers (brute + generator) were written in 6 contests, always only after the first WA
  (4607 C, 4593 C/J, 2661 J, 1051 E, 1071 A, 2575 J).
- With two local fixes, our 4607 E code passes 14,000 random tests; a 30-line brute finds its
  first bug in under a second.
- The one recorded handover (4071 A after 4 WA) was AC first try.
