#!/usr/bin/env bash
# Usage: bash stress.sh FAST BRUTE GEN [N]   e.g. bash stress.sh ./a ./brute "python3 gen.py"
# GEN gets the seed as its last argument, so a failing seed reproduces the same test.
for ((i = 1; i <= ${4:-1000}; i++)); do
  $3 $i > in
  timeout 2 $1 < in > o1 || { echo "RE/TLE seed $i"; cat in; exit 1; }
  $2 < in > o2
  diff -w o1 o2 > /dev/null || { echo "WA seed $i"; cat in; diff -w o1 o2; exit 1; }
done
echo "OK $((i - 1)) tests"
