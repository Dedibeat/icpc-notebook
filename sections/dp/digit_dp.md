### Canonical state

Scan most-significant digit first with
`(position, problem_state, tight, started)`.

- `tight`: the prefix still equals the bound, so the next digit is bounded.
- `started`: separates leading zeroes from real zero digits when length,
  adjacency, or the number zero matters.

For $[L,R]$, compute $solve(R)-solve(L-1)$. Memoize only states with
`tight == false`; tight states depend on the bound prefix. Omit `started` when
leading zeroes cannot change the property, as with digit sum.

### Common problem states

- digit sum or sum modulo $k$;
- previous digit for adjacency constraints;
- automaton node for forbidden/required substrings;
- used-digit mask;
- remainder modulo $m$.

Decide whether zero is included, reset memo between bounds/test cases, and
estimate answer overflow before choosing `long long`.
