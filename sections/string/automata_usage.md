### Aho-Corasick: duplicate patterns

Add every pattern before `build()`. Duplicate insertions count as distinct
pattern occurrences in the returned total.

```cpp
// Input: pattern "he" twice, pattern "she", then text "she".
Aho ac;
ac.add("he"); ac.add("he"); ac.add("she");
ac.build();
long long hits = ac.countMatches("she");
// Expected output: hits=3 ("she" once and "he" twice).
```

### Eertree: save a palindrome node, then finalize counts

`add(c)` returns the node for the longest palindromic suffix after adding `c`.
Save node ids while building; occurrence totals are final only after
`finishOccurrences()`.

```cpp
// Input: lowercase text "ababa", added left to right.
Eertree e;
int aba = -1;
string s = "ababa";
for (int i = 0; i < (int)s.size(); ++i) {
    int suffix = e.add(s[i]);
    if (i == 2) aba = suffix;
}
string represented = e.palindrome(aba);
int kinds = e.distinct();
e.finishOccurrences();
long long copies = e.tree[aba].occ;
// Expected: represented="aba"; kinds=5; copies=2.
```

### Suffix automaton: membership, occurrences, distinct substrings

The string constructor completes all `extend()` calls. `occurrences()` performs
the one-time occurrence propagation automatically; do not extend afterward.

```cpp
// Input: lowercase text "ababa" and query substrings "bab"/"aba".
SuffixAutomaton sam("ababa");
bool has = sam.contains("bab");
long long copies = sam.occurrences("aba");
long long kinds = sam.distinctSubstrings();
// Expected: has=true; copies=2; kinds=9.
```
