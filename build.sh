#!/usr/bin/env bash

set -e

run_tests=false

for arg in "$@"; do
    case "$arg" in
        (-t|--test) run_tests=true ;;
    esac
done

curr="$(cd "$(dirname "$0")" && pwd)"
bld_target="$curr/build"

mkdir -p "$bld_target"
cd "$bld_target"

cmake ..
cmake --build . --parallel
cpack

if [ "$run_tests" = true ]; then
    ctest --output-on-failure
fi

