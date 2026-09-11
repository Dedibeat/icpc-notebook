#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
build_dir=$(mktemp -d /tmp/icpc-hack-tests.XXXXXX)
trap 'rm -rf "$build_dir"' EXIT
flags=(-std=c++17 -O2 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS)
if [[ ${SANITIZE:-0} == 1 ]]; then
    flags+=(-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer)
fi
for name in test_hack_notebook test_lagrange_interpolation test_lagrange_general; do
    "${CXX:-g++}" "${flags[@]}" "tests/$name.cpp" -o "$build_dir/$name"
    "$build_dir/$name"
    echo "$name passed"
done
"${CXX:-g++}" "${flags[@]}" sections/hacks/unique_centroid_subsets.cpp \
    -o "$build_dir/unique_centroid_subsets"
python3 tests/test_unique_centroid_subsets.py "$build_dir/unique_centroid_subsets"
