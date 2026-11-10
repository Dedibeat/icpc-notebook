# Stress-test drills (Python)

Goal: make brute + generator + loop a five-minute reflex that runs **before** the first
submission. Our testers so far were always written after a WA (`team_bugs.md`).

Each `exNN_*.py` is a short solution that passes its sample and is wrong, with a bug class
taken from our own contests. Do not hunt the bug by reading: let the stress test find it.

## Drill (target: 10 minutes per exercise)

1. Read only the docstring (the statement). Start a timer.
2. Write `brute.py`: the dumbest correct solution, straight from the statement's definition.
3. Write `gen.py`: a tiny random test from the seed in `sys.argv[1]` (start from `tools/gen.py`).
4. Run the loop (use `python` instead of `python3` on Windows):

   ```bash
   bash ../../tools/stress.sh "python3 ex01_sum_of_maxima.py" "python3 brute.py" "python3 gen.py"
   ```

   Without bash, copy `tools/stress.py`, put your generator into its `gen()`, and run
   `python3 stress.py "python3 ex01_sum_of_maxima.py" "python3 brute.py"`.
5. Shrink the failing test by hand, find the bug, fix it, rerun until `OK`.
6. Compare with `solutions/exNN.py`. It holds the bug, a smallest failing test, the fix, and a
   brute and generator: `python3 solutions/exNN.py < in` is the brute, and
   `python3 solutions/exNN.py SEED` prints a test.

If the loop says `OK` but the code is wrong, your generator misses a case. That is the real
lesson of several exercises; go through the checklist below.

## Generator checklist

- Tiny n (1..6) and tiny values (1..3): ties, duplicates, readable failing tests.
- Zeros and negatives when allowed; degenerate totals.
- Edge parameters: n = 1, k = 1, k = n, p = 0.
- Several test cases per file when the input starts with T.
- Some maximal values (modulus, INF, overflow) and some larger n (loop caps), when the brute
  is fast enough.
- A crash or timeout counts as a failure; `stress.sh` reports it as RE/TLE.

## Exercises

| # | file | first for | from our contests |
|---|---|---|---|
| 01 | `ex01_sum_of_maxima.py` | Tamir | 1794 F |
| 02 | `ex02_pair_products.py` | Dedi | 4607 C, 1071 A |
| 03 | `ex03_cycle_lengths.py` | Dedi | 1071 G, 2661 J |
| 04 | `ex04_three_parts.py` | Tamir | 2661 B |
| 05 | `ex05_robber_tests.py` | everyone | multi-test reset |
| 06 | `ex06_max_median.py` | Erdene | 1794 G |
| 07 | `ex07_deadlines.py` | Erdene | 2661 G |
| 08 | `ex08_disjoint_intervals.py` | everyone | 4071 A, 1053 A, 2524 C |
| 09 | `ex09_tree_degrees.py` | Tamir | 2661 B |
| 10 | `ex10_divisible_pairs.py` | Dedi | 2693 F, 1096 C |
| 11 | `ex11_frog.py` | Dedi | 4593 C, 2575 L |

Everyone should do all eleven eventually; start with your own rows.

`python tests/test_stress.py` (from the repository root) checks every exercise:

- the sample passes and the documented smallest test fails;
- the reference generator finds the bug;
- the fix agrees with the brute force on 200 random tests.
