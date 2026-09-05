#!/usr/bin/env bash
# Usage: bash tools/test.sh SOL, where SOL.cpp and file "input" exist.
# Input: stdin is read from ./input.
# Output: compiler errors/warnings on the terminal; first 10000 program lines in ./output.
set -u
: "${1:?Usage: bash tools/test.sh SOL}"
if ! g++ -std=c++17 -O2 -Wall -Wextra "$1.cpp" -o "$1" \
        2> >(grep -E "error:|warning:" >&2); then
    exit 1
fi
"./$1" < input | head -10k > output
