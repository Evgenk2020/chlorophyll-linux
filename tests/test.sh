#!/usr/bin/env bash

set -e

curr="$(cd "$(dirname "$0")/.." && pwd)"
bld_target="$curr/build"

mkdir -p "$bld_target"
cd "$bld_target"

cmake .. -DBUILD_TESTING=ON
cmake --build . --target chloro_tests --parallel
ctest --output-on-failure
